#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 16 
void aes_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output);
void aes_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output);
void print_bytes(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
void aes_ecb_encrypt(const uint8_t *key, const uint8_t *plaintext, uint8_t *ciphertext) {
    aes_encrypt(key, plaintext, ciphertext);
}

void aes_ecb_decrypt(const uint8_t *key, const uint8_t *ciphertext, uint8_t *plaintext) {
    aes_decrypt(key, ciphertext, plaintext);
}
void aes_cbc_encrypt(const uint8_t *key, uint8_t *iv, const uint8_t *plaintext, uint8_t *ciphertext, size_t length) {
    uint8_t buffer[BLOCK_SIZE];
    size_t num_blocks = length / BLOCK_SIZE;

    for (size_t i = 0; i < num_blocks; i++) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            buffer[j] = plaintext[i * BLOCK_SIZE + j] ^ iv[j];
        }
        aes_encrypt(key, buffer, ciphertext + i * BLOCK_SIZE);
        memcpy(iv, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void aes_cbc_decrypt(const uint8_t *key, uint8_t *iv, const uint8_t *ciphertext, uint8_t *plaintext, size_t length) {
    uint8_t buffer[BLOCK_SIZE];
    size_t num_blocks = length / BLOCK_SIZE;
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (size_t i = 0; i < num_blocks; i++) {
        aes_decrypt(key, ciphertext + i * BLOCK_SIZE, buffer);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] = buffer[j] ^ prev_block[j];
        }
        memcpy(prev_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void aes_cfb_encrypt(const uint8_t *key, uint8_t *iv, const uint8_t *plaintext, uint8_t *ciphertext, size_t length) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (size_t i = 0; i < length; i++) {
        if (i % BLOCK_SIZE == 0) {
            aes_encrypt(key, feedback, feedback);
        }
        ciphertext[i] = plaintext[i] ^ feedback[i % BLOCK_SIZE];
    }
}

void aes_cfb_decrypt(const uint8_t *key, uint8_t *iv, const uint8_t *ciphertext, uint8_t *plaintext, size_t length) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (size_t i = 0; i < length; i++) {
        if (i % BLOCK_SIZE == 0) {
            aes_encrypt(key, feedback, feedback);
        }
        plaintext[i] = ciphertext[i] ^ feedback[i % BLOCK_SIZE];
    }
}
void aes_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output) {
    memcpy(output, input, BLOCK_SIZE);
}

void aes_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output) {
    memcpy(output, input, BLOCK_SIZE);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t iv[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t plaintext[BLOCK_SIZE] = {0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x31, 0x36, 0x20, 0x62, 0x79, 0x74, 0x65, 0x73};
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];
    aes_ecb_encrypt(key, plaintext, ciphertext);
    print_bytes("ECB Ciphertext", ciphertext, BLOCK_SIZE);
    aes_ecb_decrypt(key, ciphertext, decrypted);
    print_bytes("ECB Decrypted", decrypted, BLOCK_SIZE);
    aes_cbc_encrypt(key, iv, plaintext, ciphertext, BLOCK_SIZE);
    print_bytes("CBC Ciphertext", ciphertext, BLOCK_SIZE);
    aes_cbc_decrypt(key, iv, ciphertext, decrypted, BLOCK_SIZE);
    print_bytes("CBC Decrypted", decrypted, BLOCK_SIZE);
    aes_cfb_encrypt(key, iv, plaintext, ciphertext, BLOCK_SIZE);
    print_bytes("CFB Ciphertext", ciphertext, BLOCK_SIZE);
    aes_cfb_decrypt(key, iv, ciphertext, decrypted, BLOCK_SIZE);
    print_bytes("CFB Decrypted", decrypted, BLOCK_SIZE);

    return 0;
}
