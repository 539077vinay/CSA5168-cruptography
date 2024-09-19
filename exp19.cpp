#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

#define KEY_SIZE 24

void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output);
void des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void des_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);
void triple_des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length);

int main() {
    
    uint8_t key[KEY_SIZE] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                              0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF1,
                              0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE };
   
    uint8_t iv[BLOCK_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
   
    uint8_t plaintext[16] = { 0x49, 0x20, 0x61, 0x6D, 0x20, 0x6C, 0x65, 0x61, 
                              0x72, 0x6E, 0x69, 0x6E, 0x67, 0x20, 0x43, 0x42 };

    uint8_t ciphertext[16];

    cbc_encrypt(plaintext, key, iv, ciphertext, 16);

    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
   
    memcpy(ciphertext, plaintext, BLOCK_SIZE);
}


void des_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    
    memcpy(plaintext, ciphertext, BLOCK_SIZE);
}

void triple_des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    uint8_t temp1[BLOCK_SIZE];
    uint8_t temp2[BLOCK_SIZE];

    des_encrypt(plaintext, key, temp1);

    des_decrypt(temp1, key + 8, temp2);

    des_encrypt(temp2, key + 16, ciphertext);
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length) {
    uint8_t temp[BLOCK_SIZE];
    uint8_t block[BLOCK_SIZE];

    memcpy(temp, iv, BLOCK_SIZE);

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
     
        xorBlocks(plaintext + i, temp, block);

        triple_des_encrypt(block, key, ciphertext + i);

        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

