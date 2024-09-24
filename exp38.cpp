#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2  // For a 2x2 key matrix
#define ALPHABET_SIZE 26

// Function to find the modular inverse of a number
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % ALPHABET_SIZE;
}

// Function to find the inverse of the key matrix
void inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int det_inv = mod_inverse(det, ALPHABET_SIZE);
    if (det_inv == -1) {
        printf("Matrix is not invertible.\n");
        exit(1);
    }

    inverse[0][0] = (matrix[1][1] * det_inv) % ALPHABET_SIZE;
    inverse[0][1] = (-matrix[0][1] * det_inv + ALPHABET_SIZE) % ALPHABET_SIZE;
    inverse[1][0] = (-matrix[1][0] * det_inv + ALPHABET_SIZE) % ALPHABET_SIZE;
    inverse[1][1] = (matrix[0][0] * det_inv) % ALPHABET_SIZE;
}

// Function to encrypt plaintext using the Hill cipher
void encrypt(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};

        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < strlen(plaintext)) {
                block[j] = plaintext[i + j] - 'A';
            }
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (key[j][0] * block[0] + key[j][1] * block[1]) % ALPHABET_SIZE + 'A';
        }
    }
    ciphertext[strlen(plaintext)] = '\0';  // Null-terminate the ciphertext
}

// Function to decrypt ciphertext using the Hill cipher
void decrypt(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    inverse_matrix(key, inverse);

    for (int i = 0; i < strlen(ciphertext); i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};

        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < strlen(ciphertext)) {
                block[j] = ciphertext[i + j] - 'A';
            }
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (inverse[j][0] * block[0] + inverse[j][1] * block[1]) % ALPHABET_SIZE + 'A';
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  // Null-terminate the plaintext
}

// Function to demonstrate vulnerability to known plaintext attacks
void known_plaintext_attack(char *plaintext, char *ciphertext) {
    printf("\nKnown Plaintext Attack Simulation:\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    // The attacker can derive the key from known pairs here
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    int key[MATRIX_SIZE][MATRIX_SIZE];

    printf("Enter plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;  // Remove newline character

    printf("Enter 2x2 key matrix (4 integers from 0 to 25):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted[100];
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    // Demonstrating known plaintext attack
    known_plaintext_attack(plaintext, ciphertext);

    return 0;
}

