#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24

// Function prototypes
void des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void des_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);
void triple_des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, size_t length);
void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length);
void cbc_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, size_t length);
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output);

int main() {
    // Example key and IV for 3DES
    uint8_t key[KEY_SIZE] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                              0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF1,
                              0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE };
    
    uint8_t iv[BLOCK_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t plaintext[16] = { 0x49, 0x20, 0x61, 0x6D, 0x20, 0x6C, 0x65, 0x61,
                              0x72, 0x6E, 0x69, 0x6E, 0x67, 0x20, 0x43, 0x42 };
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    // ECB Mode Encryption
    printf("ECB Mode Encryption:\n");
    ecb_encrypt(plaintext, key, ciphertext, 16);
    printf("Ciphertext (ECB): ");
    for (int i = 0; i < 16; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    // CBC Mode Encryption
    printf("CBC Mode Encryption:\n");
    cbc_encrypt(plaintext, key, iv, ciphertext, 16);
    printf("Ciphertext (CBC): ");
    for (int i = 0; i < 16; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    return 0;
}

// Triple DES encryption
void triple_des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    uint8_t temp1[BLOCK_SIZE];
    uint8_t temp2[BLOCK_SIZE];

    // First DES encryption
    des_encrypt(plaintext, key, temp1);

    // Second DES decryption
    des_decrypt(temp1, key + 8, temp2);

    // Third DES encryption
    des_encrypt(temp2, key + 16, ciphertext);
}

// XOR two blocks of data
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// ECB mode encryption using 3DES
void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, size_t length) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        triple_des_encrypt(plaintext + i, key, ciphertext + i);
    }
}

// CBC mode encryption using 3DES
void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length) {
    uint8_t temp[BLOCK_SIZE];
    uint8_t block[BLOCK_SIZE];

    // Initialize IV for CBC mode
    memcpy(temp, iv, BLOCK_SIZE);

    // Process each block
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        // XOR plaintext with the previous ciphertext (or IV for the first block)
        xorBlocks(plaintext + i, temp, block);

        // Encrypt the block with 3DES
        triple_des_encrypt(block, key, ciphertext + i);

        // Copy ciphertext to temp for next block's XOR
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

// DES encryption function (placeholder)
void des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    // Implement the actual DES encryption here or use an external library
    memcpy(ciphertext, plaintext, BLOCK_SIZE);  // Placeholder for demo purposes
}

// DES decryption function (placeholder)
void des_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    
    memcpy(plaintext, ciphertext, BLOCK_SIZE);  
}

