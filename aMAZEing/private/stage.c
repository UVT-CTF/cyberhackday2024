#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// XOR a string with a key
void xor_string(char *str, const char *key, size_t len) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        str[i] ^= key[i % key_len];
    }
}

void some_encryption_idk(char *input, char *output) {
    for (size_t i = 0; input[i] != '\0'; ++i) {
        char c = input[i];
        if (c >= 'a' && c <= 'z') {
            output[i] = ((c - 'a' + 13) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            output[i] = ((c - 'A' + 13) % 26) + 'A';
        } else {
            output[i] = c;
        }
    }
    output[strlen(input)] = '\0';
}

// Stage 1: Check for the correct name
int check_name() {
    char input_name[50];
    printf("Hello. Welcome to my aMAZEing maze. You got it? Me neither. Anyway, I will allow only trusted members to win this. I know, it's rigged, but that's life. So let's start.\nEnter your name: ");

    scanf("%49s", input_name);

    if (strcmp(input_name, "Sup3r4dm1n") == 0) {
        return 1;
    } else {
        printf("Incorrect name.\n");
        return 0;
    }
}

// Stage 2: Check for the correct password
int check_password() {
    char input_password[50];
    char xored_password[] = {0x00,0x26,0x23,0x60,0x21,0x00,0x60,0x30,0x26,0x21,0x60,0x03,0x67,0x66,0x66}; // "Sup3rS3cur3P455" XORed with 0x53
    char decoded_password[sizeof(xored_password)];

    // Decode the XORed password
    for (int i = 0; i < sizeof(xored_password); i++) {
        decoded_password[i] = xored_password[i] ^ 0x53;
    }
    decoded_password[sizeof(xored_password)] = '\0'; // Null-terminate the decoded password

    printf("Congrats. That was actually a challenge. You are not a fool though.\nEnter your password: ");
    scanf("%49s", input_password);

    if (strcmp(input_password, decoded_password) == 0) {
        return 1;
    } else {
        printf("Incorrect password.\n");
        return 0;
    }
}

// Stage 3: Ask a question, answer stored in an offset
int check_favorite_food() {
    char input_food[50];
    char enc[] ="Cvmmn Qvnibyn";
    char food[sizeof(enc)];
    some_encryption_idk(enc, food);
     // This should be stored at an offset in real implementation

    printf("Okay. Let's take a break from this game to eat something. Anyway, what is my favourite food?\nAnswer: ");
    scanf(" %[^\n]%*c", input_food);

    if (strcmp(input_food, food) == 0) {
        return 1;
    } else {
        printf("Incorrect answer.\n");
        return 0;
    }
}

// Stage 4: Check for the correct occupation
int check_occupation() {
    char input_occupation[100];
    char xored_occupation[] = {0x06,0x2c,0x15,0x4d,0x03,0x27,0x63,0x04,0x19,0x18,0x21,0x20,0x00,0x01,0x50,0x20,0x22,0x02,0x06,0x15,0x3a,0x6f,0x41,0x0f,0x05,0x3c,0x63,0x12,0x19,0x19,0x24,0x2f,0x41,0x03,0x1f,0x3c,0x63,0x03,0x01,0x11,0x2b,0x28,0x41,0x05,0x11,0x3c,0x63,0x0e,0x03,0x15}; // "Not so ethical hacker, but still not black hat one" XORed with "HCamp"

    xor_string(xored_occupation, "HCamp", sizeof(xored_occupation));

    printf("You should know before you entered this game what is my main occupation. So, what is my main occupation?\nAnswer: ");
    scanf(" %[^\n]%*c", input_occupation);

    if (strcmp(input_occupation, xored_occupation) == 0) {
        return 1;
    } else {
        printf("Incorrect answer.\n");
        return 0;
    }
}

// Stage 5: Open and read the flag file
void read_flag() {
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("Could not open flag.txt\n");
        return;
    }

    char flag[100];
    if (fgets(flag, sizeof(flag), file) != NULL) {
        printf("Congratulations! Here is your flag: %s\n", flag);
    } else {
        printf("Failed to read the flag.\n");
    }

    fclose(file);
}

int main() {
    if (!check_name()) return 1;
    if (!check_password()) return 1;
    if (!check_favorite_food()) return 1;
    if (!check_occupation()) return 1;

    read_flag();
    return 0;
}


