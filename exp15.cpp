#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void computeFrequency(const char *text, double *freq) {
    int counts[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            counts[c - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)counts[i] / total;
    }
}
void decryptText(const char *ciphertext, int key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}
double calculateScore(const char *plaintext, const double *expectedFreq) {
    double freq[ALPHABET_SIZE] = {0};
    computeFrequency(plaintext, freq);

    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (freq[i] - expectedFreq[i]) * (freq[i] - expectedFreq[i]);
    }
    return score;
}
void frequencyAttack(const char *ciphertext, int topN) {
    double englishFreq[ALPHABET_SIZE] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
                                         0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                                         0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
                                         0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                                         0.02758, 0.00978, 0.02360, 0.00150, 0.00770};

    char plaintext[strlen(ciphertext) + 1];
    double scores[ALPHABET_SIZE];
    int keys[ALPHABET_SIZE];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decryptText(ciphertext, key, plaintext);
        scores[key] = calculateScore(plaintext, englishFreq);
        keys[key] = key;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[j] < scores[i]) {
                
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                
                int tempKey = keys[i];
                keys[i] = keys[j];
                keys[j] = tempKey;
            }
        }
    }
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        decryptText(ciphertext, keys[i], plaintext);
        printf("Key %2d: %s\n", keys[i], plaintext);
    }
}

int main() {
    char ciphertext[] = "Lzggj gz xli qebn hqebq"; 
    int topN = 10; 

    frequencyAttack(ciphertext, topN);

    return 0;
}

