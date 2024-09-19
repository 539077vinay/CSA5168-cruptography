#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10  // S-DES key size
#define IV_SIZE 8    // Initialization Vector (IV) size

// S-DES encryption/decryption functions
void sdes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void sdes_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);

// CBC mode encryption using S-DES
void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length);

// CBC mode decryption using S-DES
void cbc_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, size_t length);

// XOR two blocks of data
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output);

// Main function to test CBC mode encryption/decryption
int main() {
    uint8_t key[KEY_SIZE] = { 0x1F, 0x1D }; // Binary: 01111 11101 (S-DES key)
    uint8_t iv[IV_SIZE] = { 0xAA };         // Binary: 1010 1010 (IV)
    uint8_t plaintext[BLOCK_SIZE] = { 0x01, 0x23 }; // Binary: 0000 0001 0010 0011
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];
    size_t length = BLOCK_SIZE;

    // CBC Mode Encryption
    printf("CBC Mode Encryption:\n");
    cbc_encrypt(plaintext, key, iv, ciphertext, length);
    printf("Ciphertext (CBC): ");
    for (size_t i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    // CBC Mode Decryption
    printf("CBC Mode Decryption:\n");
    cbc_decrypt(ciphertext, key, iv, decrypted, length);
    printf("Decrypted (CBC): ");
    for (size_t i = 0; i < length; i++) printf("%02X ", decrypted[i]);
    printf("\n");

    return 0;
}

// XOR two blocks of data
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// CBC mode encryption using S-DES
void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length) {
    uint8_t temp[BLOCK_SIZE];
    uint8_t block[BLOCK_SIZE];

    memcpy(temp, iv, BLOCK_SIZE); // Initialize IV

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, temp, block); // XOR plaintext with IV or previous ciphertext
        sdes_encrypt(block, key, ciphertext + i);
        memcpy(temp, ciphertext + i, BLOCK_SIZE); // Update temp with current ciphertext
    }
}

// CBC mode decryption using S-DES
void cbc_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, size_t length) {
    uint8_t temp[BLOCK_SIZE];
    uint8_t block[BLOCK_SIZE];

    memcpy(temp, iv, BLOCK_SIZE); // Initialize IV

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        sdes_decrypt(ciphertext + i, key, block);
        xor_blocks(block, temp, plaintext + i); // XOR decrypted block with IV or previous ciphertext
        memcpy(temp, ciphertext + i, BLOCK_SIZE); // Update temp with current ciphertext
    }
}

// Placeholder for S-DES encryption (to be implemented)
void sdes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    // S-DES encryption implementation goes here
    // For simplicity, this is a placeholder
    memcpy(ciphertext, plaintext, BLOCK_SIZE); // Dummy copy (replace with actual S-DES encryption)
}

// Placeholder for S-DES decryption (to be implemented)
void sdes_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    // S-DES decryption implementation goes here
    // For simplicity, this is a placeholder
    memcpy(plaintext, ciphertext, BLOCK_SIZE); // Dummy copy (replace with actual S-DES decryption)
}

