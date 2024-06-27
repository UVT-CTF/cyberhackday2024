/*
	Variable-length code LZW compressor and decompressor for fixed-memory decoding.
	Copyright (c) 2020-2022, Eddy L O Jansson. Licensed under The MIT License.

	See https://github.com/eloj/lzw-eddy
*/

#include "lzw.h"

#define SYMBOL_BITS			8
#define SYMBOL_MASK			((1UL << SYMBOL_BITS)-1)
#define PARENT_BITS			LZW_MAX_CODE_WIDTH
#define PARENT_SHIFT		SYMBOL_BITS
#define PARENT_MASK			((1UL << PARENT_BITS)-1)
#define PREFIXLEN_BITS		LZW_MAX_CODE_WIDTH
#define PREFIXLEN_SHIFT		(PARENT_BITS+SYMBOL_BITS)
#define PREFIXLEN_MASK		((1UL << PREFIXLEN_BITS)-1)

#define CODE_CLEAR			(1UL << SYMBOL_BITS)
#define CODE_EOF			(CODE_CLEAR+1)
#define CODE_FIRST			(CODE_CLEAR+2)

static inline sym_t lzw_node_symbol(lzw_node node) {
	return node & SYMBOL_MASK;
}

static inline code_t lzw_node_parent(lzw_node node) {
	return (node >> PARENT_SHIFT) & PARENT_MASK;
}

static inline code_t lzw_node_prefix_len(lzw_node node) {
	return (node >> PREFIXLEN_SHIFT) & PREFIXLEN_MASK;
}

static inline lzw_node lzw_make_node(sym_t symbol, code_t parent, code_t len) {
	lzw_node node = (len << PREFIXLEN_SHIFT) | (parent << PARENT_SHIFT) | symbol;
	return node;
}

static inline uint32_t mask_from_width(uint32_t width) {
	return (1UL << width) - 1;
}

static void lzw_reset(struct lzw_state* state) {
	state->tree.prev_code = CODE_EOF;
	state->tree.next_code = CODE_FIRST;
	state->tree.code_width = LZW_MIN_CODE_WIDTH;
	state->must_reset = false;
}

static void lzw_init(struct lzw_state* state) {
	for (size_t i = 0; i < (1UL << SYMBOL_BITS); ++i) {
		state->tree.node[i] = lzw_make_node((sym_t)i, 0, 0);
	}
	state->rptr = 0;
	state->bitres = 0;
	state->bitres_len = 0;
	state->was_init = true;
	lzw_reset(state);
}

/*
const char* lzw_strerror(enum lzw_errors errnum) {
	const char* errstr = "Unknown error";

	switch (errnum) {
	case LZW_NOERROR:
		errstr = "No error";
		break;
	case LZW_DESTINATION_TOO_SMALL:
		errstr = "Destination buffer too small";
		break;
	case LZW_INVALID_CODE_STREAM:
		errstr = "Invalid code stream";
		break;
	case LZW_STRING_TABLE_FULL:
		errstr = "String table full";
		break;

	}
	return errstr;
}
*/

ssize_t lzw_decompress(struct lzw_state* state, uint8_t* src, size_t slen, uint8_t* dest, size_t dlen) {
	if (state->was_init == false)
		lzw_init(state);

	uint32_t bitres = state->bitres;
	uint32_t bitres_len = state->bitres_len;

	uint32_t code = 0;
	size_t wptr = 0;

	while (state->rptr < slen) {
		while ((bitres_len < state->tree.code_width) && (state->rptr < slen)) {
			bitres |= src[state->rptr++] << bitres_len;
			bitres_len += 8;
		}

		state->bitres = bitres;
		state->bitres_len = bitres_len;

		if (state->bitres_len < state->tree.code_width) {
			return LZW_INVALID_CODE_STREAM;
		}

		code = bitres & mask_from_width(state->tree.code_width);
		bitres >>= state->tree.code_width;
		bitres_len -= state->tree.code_width;

		if (code == CODE_CLEAR) {
			if (state->tree.next_code != CODE_FIRST)
				lzw_reset(state);
			continue;
		}
		else if (code == CODE_EOF) {
			break;
		}
		else if (state->must_reset) {
			return LZW_STRING_TABLE_FULL;
		}

		if (code <= state->tree.next_code) {
			bool known_code = code < state->tree.next_code;
			code_t tcode = known_code ? code : state->tree.prev_code;
			size_t prefix_len = 1 + lzw_node_prefix_len(state->tree.node[tcode]);
			uint8_t symbol = 0;

			assert(prefix_len > 0);

			if (!known_code && state->tree.prev_code == CODE_EOF) {
				return LZW_INVALID_CODE_STREAM;
			}

			if (prefix_len > state->longest_prefix) {
				state->longest_prefix = prefix_len;
			}

			if (prefix_len + (known_code ? 0 : 1) > dlen) {
				return LZW_DESTINATION_TOO_SMALL;
			}

			if (wptr + prefix_len + (known_code ? 0 : 1) > dlen) {
				return wptr;
			}

			for (size_t i = 0; i < prefix_len; ++i) {
				symbol = lzw_node_symbol(state->tree.node[tcode]);
				dest[wptr + prefix_len - 1 - i] = symbol;
				tcode = lzw_node_parent(state->tree.node[tcode]);
			}
			wptr += prefix_len;

			if (state->tree.prev_code != CODE_EOF) {
				if (!known_code) {
					assert(code == state->tree.next_code);
					assert(wptr < dlen);
					dest[wptr++] = symbol; 
				}

				state->tree.node[state->tree.next_code] = lzw_make_node(symbol, state->tree.prev_code, 1 + lzw_node_prefix_len(state->tree.node[state->tree.prev_code]));

				if (state->tree.next_code >= mask_from_width(state->tree.code_width)) {
					if (state->tree.code_width == LZW_MAX_CODE_WIDTH) {
						state->must_reset = true;
						state->tree.prev_code = code;
						continue;
					}
					++state->tree.code_width;
				}
				state->tree.next_code++;
			}
			state->tree.prev_code = code;
		}
		else {
			return LZW_INVALID_CODE_STREAM;
		}
	}
	return wptr;
}

static bool lzw_string_table_lookup(struct lzw_state* state, uint8_t* prefix, size_t len, code_t* code) {
	assert(len > 0);

	if (len == 1) {
		*code = state->tree.node[prefix[0]];
		return true;
	}

	for (size_t i = state->tree.next_code - 1; i >= CODE_FIRST; --i) {
		assert(i < LZW_MAX_CODES);
		lzw_node node = state->tree.node[i];

		if (len - 1 == lzw_node_prefix_len(node)) {
			for (size_t j = 0; j < len; ++j) {
				if (prefix[len - j - 1] != lzw_node_symbol(node)) {
					break;
				}
				if (lzw_node_prefix_len(node) == 0) {
					*code = (code_t)i;
					assert(j == len - 1);
					return true;
				}
				node = state->tree.node[lzw_node_parent(node)];
			}
		}
	}

	return false;
}

inline static void lzw_output_code(struct lzw_state* state, code_t code) {
	assert(state->bitres_len + state->tree.code_width <= sizeof(bitres_t) * 8); 
	state->bitres |= code << state->bitres_len;
	state->bitres_len += state->tree.code_width;
	state->tree.prev_code = code;

}

static void lzw_flush_reservoir(struct lzw_state* state, uint8_t* dest, bool final) {

	while (state->bitres_len >= 8) {
		dest[state->wptr++] = state->bitres & 0xFF;
		state->bitres >>= 8;
		state->bitres_len -= 8;
	}

	if (final && state->bitres_len > 0) {
		dest[state->wptr++] = state->bitres;
		state->bitres = 0;
		state->bitres_len = 0;
	}
}

ssize_t lzw_compress(struct lzw_state* state, uint8_t* src, size_t slen, uint8_t* dest, size_t dlen) {
	if (state->was_init == false) {
		lzw_init(state);
		lzw_output_code(state, CODE_CLEAR);
	}

	code_t code = CODE_EOF;
	size_t prefix_end = 0;
	state->wptr = 0;

	while (state->rptr + prefix_end < slen) {
		if (state->wptr + (state->tree.code_width >> 3) + 1 + 2 + 2 > dlen) {
			return state->wptr;
		}

		++prefix_end;
		bool overlong = ((state->longest_prefix_allowed > 0) && (prefix_end >= state->longest_prefix_allowed));
		bool existing_code = lzw_string_table_lookup(state, src + state->rptr, prefix_end, &code);
		if (!existing_code || overlong) {
			assert(code != CODE_CLEAR);
			assert(code != CODE_EOF);

			uint8_t symbol = src[state->rptr + prefix_end - 1];
			code_t parent = code;
			code_t parent_len = 1 + lzw_node_prefix_len(state->tree.node[parent]);

			lzw_output_code(state, parent);

			if (state->tree.next_code == (1UL << state->tree.code_width)
#if LZW_MAX_CODE_WIDTH == 16
				|| (state->tree.next_code == LZW_MAX_CODES - 1)
#endif
				) {
				if (state->tree.code_width < LZW_MAX_CODE_WIDTH) {
					++state->tree.code_width;
				}
				else {
					lzw_flush_reservoir(state, dest, false);
					lzw_output_code(state, CODE_CLEAR);
					lzw_reset(state);
					lzw_flush_reservoir(state, dest, false);
					state->tree.next_code = CODE_EOF;
				}
			}

			assert(state->tree.next_code < LZW_MAX_CODES);
			state->tree.node[state->tree.next_code++] = lzw_make_node(symbol, parent, parent_len);

			if (parent_len > state->longest_prefix) {
				state->longest_prefix = parent_len;
			}

			state->rptr += parent_len;
			prefix_end = 0;

			lzw_flush_reservoir(state, dest, false);
		}
	}
	if (prefix_end != 0) {
		lzw_output_code(state, code);
		lzw_flush_reservoir(state, dest, false);
		state->rptr += prefix_end;
		prefix_end = 0;
	}

	if ((state->rptr + prefix_end == slen && state->tree.prev_code != CODE_EOF) || (state->wptr == 0 && state->bitres_len > 0)) {
		lzw_output_code(state, CODE_EOF);
		lzw_flush_reservoir(state, dest, true);
	}

	assert(!(state->wptr == 0 && state->bitres_len > 0));

	return state->wptr;
}