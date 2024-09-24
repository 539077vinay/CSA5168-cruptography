#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to encrypt the plaintext using the one-time pad
void encrypt(const char *plaintext, const int *key, size_t key_length, char *ciphertext) {
    for (size_t i = 0; i < strlen(plaintext); i++) {
        // Convert plaintext character to 0-25
        int p = plaintext[i] - 'A';
        // Apply key
        int k = key[i % key_length];
        // Encrypt and handle wrapping
        int c = (p + k) % ALPHABET_SIZE;
        // Convert back to character
        ciphertext[i] = c + 'A';
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext using the one-time pad
void decrypt(const char *ciphertext, const int *key, size_t key_length, char *plaintext) {
    for (size_t i = 0; i < strlen(ciphertext); i++) {
        // Convert ciphertext character to 0-25
        int c = ciphertext[i] - 'A';
        // Apply key
        int k = key[i % key_length];
        // Decrypt and handle wrapping
        int p = (c - k + ALPHABET_SIZE) % ALPHABET_SIZE;
        // Convert back to character
        plaintext[i] = p + 'A';
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the string
}

// Function to generate a random key of specified length
void generate_random_key(int *key, size_t key_length) {
    for (size_t i = 0; i < key_length; i++) {
        key[i] = rand() % ALPHABET_SIZE; // Random number between 0 and 25
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char plaintext[100];
    printf("Enter plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline

    size_t key_length = strlen(plaintext);
    int key[key_length];

    // Generate a random key
    generate_random_key(key, key_length);

    // Encrypt the plaintext
    char ciphertext[100];
    encrypt(plaintext, key, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted[100];
    decrypt(ciphertext, key, key_length, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    // Print the key for reference
    printf("Key: ");
    for (size_t i = 0; i < key_length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    return 0;
}

