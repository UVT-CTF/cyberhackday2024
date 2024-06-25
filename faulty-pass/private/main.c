#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD_LENGTH 80

void generate_password(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    int charset_size = sizeof(charset) - 1;
    
    for (int i = 0; i < length; i++) {
        int key = rand() % charset_size;
        password[i] = charset[key];
    }
    password[length] = '\0';
}

int main() {
    srand(time(NULL));

    char password[PASSWORD_LENGTH + 1];
    generate_password(password, PASSWORD_LENGTH);

    printf("Generated Password: %s\n", password);

    return 0;
}
