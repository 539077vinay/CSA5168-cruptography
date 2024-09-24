#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if two numbers are coprime
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt using the affine Caesar cipher
char encrypt(int a, int b, char p) {
    // Ensure p is uppercase A-Z
    if (p < 'A' || p > 'Z') {
        return p; // Return unchanged if not a letter
    }
    return 'A' + (a * (p - 'A') + b) % 26;
}

// Function to find modular inverse of a mod 26
int mod_inverse(int a) {
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) {
            return x;
        }
    }
    return -1; // Return -1 if no modular inverse exists
}

// Function to decrypt using the affine Caesar cipher
char decrypt(int a, int b, char c) {
    // Ensure c is uppercase A-Z
    if (c < 'A' || c > 'Z') {
        return c; // Return unchanged if not a letter
    }
    int a_inv = mod_inverse(a);
    if (a_inv == -1) {
        printf("No modular inverse exists for a = %d, decryption impossible.\n", a);
        return c; // Cannot decrypt
    }
    return 'A' + (a_inv * ((c - 'A') - b + 26)) % 26;
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    // Remove newline character from the input
    plaintext[strcspn(plaintext, "\n")] = 0;

    printf("Enter values for a and b (0 <= a < 26, 0 <= b < 26): ");
    scanf("%d %d", &a, &b);

    // Check if 'a' is coprime with 26
    if (gcd(a, 26) != 1) {
        printf("Value of a must be coprime with 26 for the cipher to be one-to-one.\n");
        return 1;
    }

    // Encrypt the plaintext
    printf("Ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = encrypt(a, b, plaintext[i]);
        putchar(c);
    }
    putchar('\n');

    // Decrypt the ciphertext
    printf("Decrypted text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char p = decrypt(a, b, plaintext[i]);
        putchar(p);
    }
    putchar('\n');

    return 0;
}

