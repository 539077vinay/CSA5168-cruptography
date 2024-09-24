#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8  // 64-bit block size (in bytes)
#define BLOCK_SIZE_128 16 // 128-bit block size (in bytes)

// Function to print a block in hexadecimal
void print_block(uint8_t* block, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", block[i]);
    }
    printf("\n");
}

// Function to left shift a block by 1 bit
void left_shift_block(uint8_t* block, size_t size) {
    uint8_t overflow = 0;
    for (int i = size - 1; i >= 0; i--) {
        uint8_t new_overflow = block[i] >> 7; // MSB to carry
        block[i] = (block[i] << 1) | overflow; // Left shift with carry
        overflow = new_overflow;
    }
}

// Function to XOR a block with a constant
void xor_block(uint8_t* block, uint8_t* constant, size_t size) {
    for (size_t i = 0; i < size; i++) {
        block[i] ^= constant[i];
    }
}

// Function to generate the CMAC subkeys K1 and K2
void cmac_subkey_generation(uint8_t* key, size_t block_size, uint8_t* K1, uint8_t* K2, uint8_t Rb) {
    uint8_t L[block_size];
    memset(L, 0, block_size);

    // Simulate block cipher encryption of an all-zero block with the secret key (just use key XOR here for demo)
    xor_block(L, key, block_size); // In real scenario, this should be a block cipher encryption

    printf("L (encryption of zero block): ");
    print_block(L, block_size);

    // Generate K1 by left-shifting L and conditionally XORing with Rb if MSB is 1
    memcpy(K1, L, block_size);
    left_shift_block(K1, block_size);
    if (L[0] & 0x80) { // Check if MSB of L is 1
        K1[block_size - 1] ^= Rb; // XOR with the Rb constant
    }

    printf("K1 (first subkey): ");
    print_block(K1, block_size);

    // Generate K2 by left-shifting K1 and conditionally XORing with Rb if MSB is 1
    memcpy(K2, K1, block_size);
    left_shift_block(K2, block_size);
    if (K1[0] & 0x80) { // Check if MSB of K1 is 1
        K2[block_size - 1] ^= Rb; // XOR with the Rb constant
    }

    printf("K2 (second subkey): ");
    print_block(K2, block_size);
}

int main() {
    // Define block size and constants for 128-bit blocks
    size_t block_size = BLOCK_SIZE_128;
    uint8_t Rb_128 = 0x87; // 128-bit Rb constant for AES

    // Secret key (for demonstration purposes)
    uint8_t key[BLOCK_SIZE_128] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0xcf, 0x35, 0x8e, 0x4a, 0x53, 0xf0
    };

    // Buffers for subkeys K1 and K2
    uint8_t K1[BLOCK_SIZE_128];
    uint8_t K2[BLOCK_SIZE_128];

    // Generate subkeys for 128-bit block size
    printf("Subkey generation for 128-bit block size:\n");
    cmac_subkey_generation(key, block_size, K1, K2, Rb_128);

    return 0;
}

