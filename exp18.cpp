#include <stdio.h>
#include <stdint.h>


int PC1[56] = { /* Permuted Choice 1 for key generation */ };
int PC2[48] = { /* Permuted Choice 2 for key generation */ };
int shiftSchedule[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void applyPermutation(uint64_t input, uint64_t *output, int *permTable, int size);
void shiftLeft(uint32_t *halfKey, int shifts);
void generateSubKeys(uint64_t key, uint64_t *subKeys);

void generateSubKeys(uint64_t key, uint64_t *subKeys) {
    uint64_t permutedKey;
    uint32_t C, D;

    applyPermutation(key, &permutedKey, PC1, 56);

    C = (uint32_t)(permutedKey >> 28);  
    D = (uint32_t)(permutedKey & 0x0FFFFFFF); 

    for (int i = 0; i < 16; i++) {
        
        shiftLeft(&C, shiftSchedule[i]);
        shiftLeft(&D, shiftSchedule[i]);

        uint64_t combined = ((uint64_t)C << 28) | D;

        applyPermutation(combined, &subKeys[i], PC2, 48);
    }
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
    uint64_t key = 0x133457799BBCDFF1;        
    uint64_t subKeys[16];                    

    generateSubKeys(key, subKeys);

    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: %012llX\n", i + 1, subKeys[i]);
    }

    return 0;
}

