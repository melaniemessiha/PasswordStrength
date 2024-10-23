#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PW_LENGTH 256

bool isPassphrase(const char *password);
bool cnum_Length(const char *password, int minL, int maxL);
bool cnum_Repeats(const char *password);
bool cnum_Characters(const char *password);
bool cnum_Lowercase(const char *password);
bool cnum_Uppercase(const char *password);
bool cmin_Digits(const char *password, int min_digits);
bool cmin_Special(const char *password, int min_special);
int cOptional(const char *password);

int main() {
    const char *files[] = {"Proposed Passwords #1.txt", "Proposed Passwords #2.txt", "Proposed Passwords #3.txt"};
    int file_count = 3;

    //read each of the 3 files
    for (int i = 0; i < file_count; i++) {
        FILE *file = fopen(files[i], "r");
        if (!file) {
            printf("Failed to open file: %s\n", files[i]);
            return 1;
        }

        int maxL, minL, allowPassphrases, min_phrase, require_optional, min_optional_passes;
        fscanf(file, "%d %d %d", &maxL, &minL, &allowPassphrases);
        if (allowPassphrases) {
            fscanf(file, "%d", &min_phrase);
        }
        fscanf(file, "%d %d", &require_optional, &min_optional_passes);

        //Show configuration information
        printf("\nProcessing password file #%d\n\n", i + 1);
        printf("Maximum password length: %d\n", maxL);
        printf("Minimum password length: %d\n", minL);
        if (allowPassphrases) {
            printf("Pass phrases are allowed\n");
            printf("Minimum phrase length: %d\n", min_phrase);
        } else {
            printf("Pass phrases are NOT allowed\n");
        }
        if (require_optional) {
            printf("Optional Tests are required\n");
            printf("Number of optional tests that must be passed: %d\n", min_optional_passes);
        } else {
            printf("Optional Tests are NOT required\n");
        }

        char password[MAX_PW_LENGTH];
        while (fgets(password, sizeof(password), file)) {
            //remove the newline character if it exists
            int len = strlen(password);
            if (len > 0 && password[len - 1] == '\n') {
                password[len - 1] = '\0';
            }

            //checks if the pw is a pass phrase
            bool isPhrase = isPassphrase(password);
            int min_length = minL;
            if (isPhrase && allowPassphrases) {
                min_length = min_phrase;
            }

            // Skip empty passwords
            if (strlen(password) == 0) {
                continue; // Skip to the next iteration if empty
            }

            //display the potential password which is the password data in the files
            printf("\nPotential password: %s\n", password);

            //check pw length
            bool length_check = true; 
            if (isPhrase && allowPassphrases) {
                    // passphrases check only the minimum phrase length
                if (strlen(password) < min_phrase) {
                    printf("The password must be at least %d characters long.\n", min_phrase);
                    length_check = false; 
                }
            } else {
                    length_check = cnum_Length(password, min_length, maxL);
            }

            bool repeats_check = cnum_Repeats(password);
            bool characters_check = cnum_Characters(password);
            bool strong = length_check && repeats_check && characters_check;


            // Handle required error messages
            if (!length_check) {
                printf("Password failed - it cannot be used.\n");
                continue; 
            }
            if (!repeats_check) {
                printf("The password may not contain a sequence of three or more repeated characters.\n");
                printf("Password failed - it cannot be used.\n");
                continue; 
            }
            if (!characters_check) {
                printf("The password must contain letters, numbers, AND symbols.\n");
                printf("Password failed - it cannot be used.\n");
                continue; 
            }

            //Checks if optional tests are required and then runs each test function
            int optional_passes = 0;
            if (require_optional) {
                if (cnum_Lowercase(password)) {
                    optional_passes++;
                }
                if (cnum_Uppercase(password)) {
                    optional_passes++;
                }
                if (cmin_Digits(password, 2)) {
                    optional_passes++;
                }
                if (cmin_Special(password, 2)) {
                    optional_passes++;
                }
                if (optional_passes < min_optional_passes) {
                    printf("Password failed - not enough optional tests passed. (Failed Tests: %d, Passed Tests: %d)\n", 4 - min_optional_passes, optional_passes);
                    continue; 
                }
            }
            printf("Password is valid.\n");
        }
        fclose(file);
    }
    return 0;
}

bool isPassphrase(const char *password) {
    return strchr(password, ' ') != NULL;
}

//verifies the length of the pw. Two required error messages are here in this function.
bool cnum_Length(const char *password, int minL, int maxL) {
    int length = strlen(password);
    if (length < minL) {
        printf("The password must be at least %d characters long.\n", minL);
        return false;
    }
    if (length >= maxL) {
        printf("The password must be fewer than %d characters.\n", maxL);
        return false; 
    }
    return true; 
}

//function checks the character count and if there are 3+ repeats
bool cnum_Repeats(const char *password) {
    int count = 1; 
    for (int i = 1; password[i] != '\0'; i++) {
        if (password[i] == password[i - 1]) {
            count++;
            if (count >= 3) {
                return false; 
            }
        } else {
            count = 1;
        }
    }
    return true;
}

//checks for letter, digits, and symbols
bool cnum_Characters(const char *password) {
    bool letter = false, digit = false, symbol = false;

    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letter = true;
        } else if (c >= '0' && c <= '9') {
            digit = true;
        } else {
            symbol = true;  
        }
    }

    return letter && digit && symbol;
}

bool cnum_Lowercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            return true;
        }
    }
    printf("The password must contain at least one lowercase letter.\n");
    return false;
}

bool cnum_Uppercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            return true;
        }
    }
    printf("The password must contain at least one uppercase letter.\n");
    return false;
}

bool cmin_Digits(const char *password, int min_digits) {
    int count = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] >= '0' && password[i] <= '9') {
            count++;
        }
    }
    if (count < min_digits) {
        printf("The password must contain at least two numbers.\n");
        return false;
    }
    return true;
}

bool cmin_Special(const char *password, int min_special) {
    int count = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (!((c >= '0' && c <= '9') || 
              (c >= 'A' && c <= 'Z') || 
              (c >= 'a' && c <= 'z'))) {
            count++;
        }
    }
    if (count < min_special) {
        printf("The password must contain at least two special characters.\n");
        return false;
    }
    return true;
}

int cOptional(const char *password) {
    return 0; 
}
