#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// Function to count letter frequency
void letter_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

// Function to generate possible plaintexts based on frequency
void generate_possible_plaintexts(const char *ciphertext, int *frequency, int num_candidates) {
    // Assuming 'E' (index 4) is the most common letter in English
    int max_freq_index = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[max_freq_index]) {
            max_freq_index = i;
        }
    }

    // Determine shift based on max frequency index
    int shift = (max_freq_index - 4 + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("Top %d possible plaintexts:\n", num_candidates);
    for (int i = 0; i < num_candidates; i++) {
        char possible_plaintext[strlen(ciphertext) + 1];
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (ciphertext[j] >= 'A' && ciphertext[j] <= 'Z') {
                possible_plaintext[j] = (ciphertext[j] - 'A' - (shift + i) + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
            } else {
                possible_plaintext[j] = ciphertext[j];
            }
        }
        possible_plaintext[strlen(ciphertext)] = '\0';  // Null-terminate
        printf("%d: %s\n", i + 1, possible_plaintext);
    }
}

int main() {
    char ciphertext[100];
    int frequency[ALPHABET_SIZE] = {0};
    int num_candidates;

    printf("Enter the ciphertext (uppercase letters only): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  // Remove newline character

    printf("Enter the number of top possible plaintexts to generate (up to %d): ", MAX_PLAINTEXTS);
    scanf("%d", &num_candidates);
    if (num_candidates > MAX_PLAINTEXTS) {
        num_candidates = MAX_PLAINTEXTS;
    }

    // Count letter frequency
    letter_frequency(ciphertext, frequency);

    // Generate possible plaintexts
    generate_possible_plaintexts(ciphertext, frequency, num_candidates);

    return 0;
}

