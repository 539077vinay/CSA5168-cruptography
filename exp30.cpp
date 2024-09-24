#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function to simulate XOR of two blocks (XORing two 16-byte blocks)
void xor_blocks(uint8_t* result, uint8_t* block1, uint8_t* block2, size_t block_size) {
    for (size_t i = 0; i < block_size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// Function to simulate a block cipher encryption (e.g., AES-128) using a simple XOR for illustration purposes
void block_cipher_encrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t* key, size_t block_size) {
    // In a real CBC-MAC, you would use AES or another block cipher here.
    // For simplicity, we'll just XOR the plaintext with the key as a placeholder.
    xor_blocks(ciphertext, plaintext, key, block_size);
}

// Function to compute CBC-MAC of a one-block message X
void cbc_mac_one_block(uint8_t* tag, uint8_t* key, uint8_t* message_block, size_t block_size) {
    // CBC-MAC for a one-block message is simply the encryption of the block
    block_cipher_encrypt(tag, message_block, key, block_size);
}

int main() {
    // Define block size (e.g., 16 bytes for AES-128)
    const size_t BLOCK_SIZE = 16;

    // Secret key (16 bytes)
    uint8_t key[BLOCK_SIZE] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0xcf, 0x35, 0x8e, 0x4a, 0x53, 0xf0
    };

    // One-block message X (16 bytes)
    uint8_t message_X[BLOCK_SIZE] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
    };

    // Tag (MAC) for the one-block message X
    uint8_t tag_T[BLOCK_SIZE];

    // Compute CBC-MAC for the one-block message X
    cbc_mac_one_block(tag_T, key, message_X, BLOCK_SIZE);

    printf("CBC-MAC for one-block message X (Tag T): ");
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", tag_T[i]);
    }
    printf("\n");

    // Adversary knows X and T, and now tries to compute CBC-MAC for a two-block message: X || (X ? T)

    // Compute (X ? T)
    uint8_t X_xor_T[BLOCK_SIZE];
    xor_blocks(X_xor_T, message_X, tag_T, BLOCK_SIZE);

    printf("Second block (X ? T): ");
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", X_xor_T[i]);
    }
    printf("\n");

    // Now, the two-block message is X || (X ? T)
    // CBC-MAC for this two-block message can be computed as:
    // 1. Encrypt the first block (X): C1 = Enc(K, X)
    // 2. XOR the result with the second block (X ? T), and encrypt: T' = Enc(K, C1 ? (X ? T))

    // Step 1: Encrypt the first block (X)
    uint8_t C1[BLOCK_SIZE];
    block_cipher_encrypt(C1, message_X, key, BLOCK_SIZE);

    // Step 2: XOR C1 with (X ? T) and encrypt
    uint8_t C1_xor_X_xor_T[BLOCK_SIZE];
    xor_blocks(C1_xor_X_xor_T, C1, X_xor_T, BLOCK_SIZE);

    uint8_t new_tag[BLOCK_SIZE];
    block_cipher_encrypt(new_tag, C1_xor_X_xor_T, key, BLOCK_SIZE);

    printf("CBC-MAC for two-block message X || (X ? T) (New Tag): ");
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", new_tag[i]);
    }
    printf("\n");

    return 0;
}

