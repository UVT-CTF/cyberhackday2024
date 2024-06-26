#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// HCamp{Wh0_7h0ugh7_Th15_1sNt_4_p1c??}

const int values[] = {130, 119, 89, 101, 106, 111, 139, 98, 42, 147, 43, 98, 42, 109, 91, 98, 43, 147, 142, 98, 41, 45, 147, 41, 103, 132, 110, 147, 46, 147, 106, 41, 87, 51, 51, 117};

int main() {
	int i;
	char input[37];
	puts("You found my lock. But you need to prove me you are who I think you are. Give me the passphrase: ");
	fgets(input, 37, stdin);

	if(strlen(input) != 36) {
		puts("Nah");
		exit(1);
	} 

	for(i = 0; i < strlen(input); i++) {
		int val = (input[i] ^ 0x23) + 23;
		if(val != values[i]) {
			puts("Who are you? Get out of here!!!");
			exit(2);
		}
	}
	printf("Welcome back, buddy!!! Submit this as a flag.");

	return 0;
}
