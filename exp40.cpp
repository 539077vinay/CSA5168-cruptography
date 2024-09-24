#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10
#define MAX_CIPHERTEXT_LENGTH 100

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
    // Most common letters in English
    const char *common_letters = "ETAOINSRHLDCUMWFGYPBVKXQJZ";

    // Calculate the mapping from ciphertext to plaintext
    char mapping[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[i] = 'A'; // Initialize with identity mapping
    }

    // Create a simple mapping based on frequency
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int max_index = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > frequency[max_index]) {
                max_index = j;
            }
        }
        mapping[max_index] = common_letters[i];
        frequency[max_index] = -1; // Mark as used
    }

    // Generate possible plaintexts
    printf("Top %d possible plaintexts:\n", num_candidates);
    for (int i = 0; i < num_candidates; i++) {
        char possible_plaintext[MAX_CIPHERTEXT_LENGTH + 1];
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (ciphertext[j] >= 'A' && ciphertext[j] <= 'Z') {
                possible_plaintext[j] = mapping[ciphertext[j] - 'A'];
            } else {
                possible_plaintext[j] = ciphertext[j];
            }
        }
        possible_plaintext[strlen(ciphertext)] = '\0'; // Null-terminate
        printf("%d: %s\n", i + 1, possible_plaintext);
        // Generate a new mapping for the next candidate (if needed)
        // This can be expanded for more sophisticated variations.
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    int frequency[ALPHABET_SIZE] = {0};
    int num_candidates;

    printf("Enter the ciphertext (uppercase letters only): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character

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

