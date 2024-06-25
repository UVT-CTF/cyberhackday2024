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
    // Set the specific date and time: February 15, 2023, 12:00:00 PM (noon)
    struct tm specific_time;
    specific_time.tm_year = 2023 - 1900; // Years since 1900
    specific_time.tm_mon = 1; // Month of the year (0 to 11, so 1 for February)
    specific_time.tm_mday = 3; // Day of the month
    specific_time.tm_hour = 12; // Hours since midnight (0 to 23)
    specific_time.tm_min = 0; // Minutes after the hour (0 to 59)
    specific_time.tm_sec = 0; // Seconds after the minute (0 to 59)
    specific_time.tm_isdst = -1; // Daylight saving time flag (-1 for unknown)

    // Convert specific time to timestamp
    time_t timestamp = mktime(&specific_time);
    if (timestamp == -1) {
        perror("mktime failed");
        return 1;
    }

    srand(timestamp);

    char password[PASSWORD_LENGTH + 1];
    generate_password(password, PASSWORD_LENGTH);

    printf("Generated Password: %s\n", password);
    printf("Timestamp: %ld\n", (long)timestamp);

    return 0;
}
