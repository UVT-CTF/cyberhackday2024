#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *password = "aaa9402664f1a41f40ebbc52c9993eb66aeb366602958fdfaa283b71e64db123";
    char *endpoint = "http://85.120.206.114:65002"; // Production
    // char *endpoint = "http://localhost:65002"; // Development
    char input[65];
    char command[256];

    printf("Enter the password: ");
    scanf("%64s", input);

    if (strcmp(input, password) == 0) {
        printf("Correct password!\n");

        snprintf(command, sizeof(command), "curl -X POST -d 'password=%s' %s", input, endpoint);

        if (strlen(command) >= sizeof(command)) {
            fprintf(stderr, "Command buffer overflow detected.\n");
            return 1;
        }

        int ret = system(command);
        if (ret == -1) {
            perror("system");
            return 1;
        }
    } else {
        printf("Incorrect password!\n");
    }

    return 0;
}
