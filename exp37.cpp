#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000
#define TOP_PLAINTEXTS 10

// English letter frequencies (in percentage)
const double ENGLISH_FREQ[ALPHABET_SIZE] = {
    8.167,  // A
    1.492,  // B
    2.782,  // C
    4.253,  // D
    12.702, // E
    2.228,  // F
    2.015,  // G
    6.094,  // H
    6.966,  // I
    0.153,  // J
    5.987,  // K
    6.949,  // L
    4.025,  // M
    2.406,  // N
    6.749,  // O
    7.507,  // P
    2.017,  // Q
    4.253,  // R
    5.987,  // S
    6.327,  // T
    9.056,  // U
    2.758,  // V
    0.978,  // W
    2.360,  // X
    1.500,  // Y
    0.074   // Z
};

// Function to calculate letter frequency in the ciphertext
void calculate_frequency(const char *ciphertext, double *frequency) {
    int total_letters = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A']++;
            total_letters++;
        } else if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
            total_letters++;
        }
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = (frequency[i] / total_letters) * 100; // Convert to percentage
    }
}

// Function to print possible plaintexts based on frequency analysis
void print_possible_plaintexts(double *frequency) {
    // Create a mapping of frequency to characters
    char mapping[ALPHABET_SIZE];
    char letters[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = 'A' + i;
    }

    // Sort the letters based on frequency
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[i] < frequency[j]) {
                // Swap frequency
                double temp_freq = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp_freq;

                // Swap letters
                char temp_char = letters[i];
                letters[i] = letters[j];
                letters[j] = temp_char;
            }
        }
    }

    // Map the most frequent letters to typical English letters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[letters[i] - 'A'] = 'A' + i; // Map the letter with highest frequency to A, etc.
    }

    // Print top possible plaintexts
    printf("Possible Plaintexts:\n");
    for (int i = 0; i < TOP_PLAINTEXTS; i++) {
        printf("%c -> %c\n", letters[i], mapping[letters[i] - 'A']);
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    double frequency[ALPHABET_SIZE] = {0};

    printf("Enter the ciphertext (uppercase letters only): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Calculate letter frequency
    calculate_frequency(ciphertext, frequency);
    
    // Print possible plaintexts based on frequency analysis
    print_possible_plaintexts(frequency);

    return 0;
}

