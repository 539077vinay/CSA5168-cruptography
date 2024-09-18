#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void generateCipher(char cipher[ALPHABET_SIZE], const char *keyword) {
    int used[ALPHABET_SIZE] = {0};  
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
}
void encrypt(char *plaintext, char *cipher, char *encrypted) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            encrypted[i] = cipher[ch - 'A'];
        } else {
            encrypted[i] = plaintext[i];  
        }
    }
    encrypted[strlen(plaintext)] = '\0';  
}
void decrypt(char *ciphertext, char *cipher, char *decrypted) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        } else {
            decrypted[i] = ciphertext[i];  
        }
    }
    decrypted[strlen(ciphertext)] = '\0';  
}

int main() {
    char keyword[] = "CIPHER";
    char cipher[ALPHABET_SIZE];
    char plaintext[100], encrypted[100], decrypted[100];
    generateCipher(cipher, keyword);
    printf("Generated cipher alphabet:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");
    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    encrypt(plaintext, cipher, encrypted);
    printf("Encrypted message: %s\n", encrypted);
    decrypt(encrypted, cipher, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

