#include <stdio.h>
#include <stdint.h>;
int IP[64] = { /* Initial permutation array */ };
int FP[64] = { /* Final permutation array */ };
int E[48] = { /* Expansion table for Feistel function */ };
int P[32] = { /* Permutation table for Feistel function */ };
int PC1[56] = { /* Permuted Choice 1 for key generation */ };
int PC2[48] = { /* Permuted Choice 2 for key generation */ };
int shiftSchedule[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int S[8][4][16] = { /* S-box values */ };

void applyPermutation(uint64_t input, uint64_t *output, int *permTable, int size);
void feistel(uint32_t *right, uint64_t subKey);
void generateSubKeys(uint64_t key, uint64_t *subKeys);
void shiftLeft(uint32_t *halfKey, int shifts);

uint64_t DES_decrypt(uint64_t ciphertext, uint64_t key) {
    uint32_t left, right, temp;
    uint64_t permutedBlock;
    uint64_t subKeys[16];

    applyPermutation(ciphertext, &permutedBlock, IP, 64);

    left = (uint32_t)(permutedBlock >> 32);
    right = (uint32_t)(permutedBlock);

    generateSubKeys(key, subKeys);

    for (int i = 15; i >= 0; i--) {
        temp = right;
        feistel(&right, subKeys[i]);
        right = left ^ right; 
        left = temp;
    }

    permutedBlock = ((uint64_t)right << 32) | left;
    applyPermutation(permutedBlock, &ciphertext, FP, 64);

    return ciphertext;
}

void generateSubKeys(uint64_t key, uint64_t *subKeys) {
    uint64_t permutedKey;
    uint32_t left, right;

    applyPermutation(key, &permutedKey, PC1, 56);

    left = (uint32_t)(permutedKey >> 28);
    right = (uint32_t)(permutedKey & 0x0FFFFFFF);

    for (int i = 0; i < 16; i++) {
        
        shiftLeft(&left, shiftSchedule[i]);
        shiftLeft(&right, shiftSchedule[i]);

        uint64_t combined = ((uint64_t)left << 28) | right;
        applyPermutation(combined, &subKeys[i], PC2, 48);
    }
}

void feistel(uint32_t *right, uint64_t subKey) {
    uint64_t expandedRight = 0;
    uint32_t sboxInput, sboxOutput = 0;

    applyPermutation(*right, &expandedRight, E, 48);

    expandedRight ^= subKey;

    for (int i = 0; i < 8; i++) {
        sboxInput = (expandedRight >> (42 - 6 * i)) & 0x3F; // Take 6 bits
        sboxOutput = (sboxOutput << 4) | S[i][(sboxInput >> 4) & 0x03][sboxInput & 0x0F];
    }

    applyPermutation(sboxOutput, (uint64_t*)right, P, 32);
}

void applyPermutation(uint64_t input, uint64_t *output, int *permTable, int size) {
    *output = 0;  
    for (int i = 0; i < size; i++) {
        *output |= ((input >> (64 - permTable[i])) & 0x01) << (size - i - 1);
    }
}

void shiftLeft(uint32_t *halfKey, int shifts) {
    *halfKey = ((*halfKey << shifts) & 0x0FFFFFFF) | ((*halfKey >> (28 - shifts)) & 0x0FFFFFFF);
}

int main() {
    uint64_t ciphertext = 0x0123456789ABCDEF;  
    uint64_t key = 0x133457799BBCDFF1;        

    uint64_t decrypted = DES_decrypt(ciphertext, key);
    printf("Decrypted message: %016llX\n", decrypted);

    return 0;
}

