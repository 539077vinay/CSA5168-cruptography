#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void normalizeKey(int* key, int keyLength, int* normalizedKey, int textLength) {
    for (int i = 0; i < textLength; i++) {
        normalizedKey[i] = key[i % keyLength];
    }
}
void encryptMessage(const char* plaintext, const int* key, int keyLength, char* ciphertext) {
    int textLength = strlen(plaintext);
    int normalizedKey[textLength];
    normalizeKey((int*)key, keyLength, normalizedKey, textLength);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + normalizedKey[i]) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLength] = '\0';
}
void decryptMessage(const char* ciphertext, const int* key, int keyLength, char* plaintext) {
    int textLength = strlen(ciphertext);
    int normalizedKey[textLength];
    normalizeKey((int*)key, keyLength, normalizedKey, textLength);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - normalizedKey[i] + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[textLength] = '\0'; 
}

int main() {
    char plaintext[] = "Meet me at the park.";
    int key[] = {3, 19, 5}; 
    int keyLength = sizeof(key) / sizeof(key[0]);

    char ciphertext[strlen(plaintext) + 1];
    char decryptedText[strlen(plaintext) + 1];

    encryptMessage(plaintext, key, keyLength, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    decryptMessage(ciphertext, key, keyLength, decryptedText);
    printf("Decrypted message: %s\n", decryptedText);

    return 0;
}

