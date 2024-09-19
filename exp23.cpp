#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10  
#define COUNTER_SIZE 8

void sdes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void sdes_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);

void ctr_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *counter, uint8_t *ciphertext, size_t length);
void ctr_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *counter, uint8_t *plaintext, size_t length);

void increment_counter(uint8_t *counter);

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output);

int main() {
    uint8_t key[KEY_SIZE] = { 0x1F, 0x1D }; // Binary: 01111 11101 (S-DES key)
    uint8_t counter[COUNTER_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Binary: 0000 0000
    uint8_t plaintext[BLOCK_SIZE] = { 0x01, 0x20, 0x40 }; // Binary: 0000 0001 0000 0010 0000 0100
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];
    size_t length = BLOCK_SIZE;

    printf("CTR Mode Encryption:\n");
    ctr_encrypt(plaintext, key, counter, ciphertext, length);
    printf("Ciphertext (CTR): ");
    for (size_t i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    memset(counter, 0x00, COUNTER_SIZE);

    printf("CTR Mode Decryption:\n");
    ctr_decrypt(ciphertext, key, counter, decrypted, length);
    printf("Decrypted (CTR): ");
    for (size_t i = 0; i < length; i++) printf("%02X ", decrypted[i]);
    printf("\n");

    return 0;
}

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void increment_counter(uint8_t *counter) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        if (++counter[i] != 0) break;
    }
}

void ctr_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *counter, uint8_t *ciphertext, size_t length) {
    uint8_t keystream[BLOCK_SIZE];

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        sdes_encrypt(counter, key, keystream);
        xor_blocks(plaintext + i, keystream, ciphertext + i);
        increment_counter(counter); 
    }
}

void ctr_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *counter, uint8_t *plaintext, size_t length) {
    uint8_t keystream[BLOCK_SIZE];

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        sdes_encrypt(counter, key, keystream);
        xor_blocks(ciphertext + i, keystream, plaintext + i);
        increment_counter(counter); 
    }
}

void sdes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    
    memcpy(ciphertext, plaintext, BLOCK_SIZE); 
}

void sdes_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {

    memcpy(plaintext, ciphertext, BLOCK_SIZE); 
}

