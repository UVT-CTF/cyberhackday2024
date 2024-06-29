#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void read_flag() {
    char buf; // buffer to hold each character read from the file
    int fd; // file descriptor for the flag file
    

    

    // Open the flag file
    fd = open("./flag.txt", O_RDONLY);
    if (fd < 0) {
        perror("\nError opening flag.txt, please contact an Administrator.\n");
        exit(1);
    }

    // Read each character from the file and print it
    while (read(fd, &buf, 1) > 0) {
        fputc(buf, stdout);
    }

    // Close the file
    close(fd);

    // Return the stack canary difference (for stack protection, not applicable in standard C)
    
}

int read_num() {
    int n;
    scanf("%d", &n);
    return n;
}

void menu() {
    int num;
    int v1; // first number input
    int v2; // second number input
    int v3; // sum of v1 and v2
    unsigned int v4;

    
    while (1) {
        v1 = 0;
        v2 = 0;
        v3 = 0;
        fwrite(
            "\n"
            "+---------------------+\n"
            "| Wandering Riddleman |\n"
            "+---------------------+\n"
            "|                     |\n"
            "| 1. Play game        |\n"
            "| 2. View hint        |\n"
            "|                     |\n"
            "+---------------------+\n"
            "\n"
            ">> ",
            1uLL,
            0xC5uLL,
            stdout
        );

        num = read_num();
        if (num == 1) {
            fwrite("\nEnter number 1: ", 1uLL, 0x11uLL, stdout);
            scanf("%d", &v1);
            fwrite("\nEnter number 2: ", 1uLL, 0x11uLL, stdout);
            scanf("%d", &v2);

            if (v2 < 0 || v1 < 0) {
                fprintf(stdout, "\n%s[-] Invalid input!\n", "\x1B[1;31m");
                exit(123);
            }

            v3 = v1 + v2;
            if (v1 + v2 < 0) {
                fwrite("\n[+] You are very wise! Here is your gift: \n", 1uLL, 0x2CuLL, stdout);
                read_flag();
            } else {
                fprintf(stdout, "%s\n[-] The sum is positive!\n%s", "\x1B[1;31m", "\x1B[1;34m");
            }
        } else if (num != 2) {
            fwrite("\nGoodbye!\n\n", 1uLL, 0xBuLL, stdout);
            exit(22);
        }

        fwrite("\nIt's riddle time! Enter 2 numbers where n1, n2 > 0 and n1 + n2 < 0\n", 1uLL, 0x44uLL, stdout);
    }
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    menu();
}