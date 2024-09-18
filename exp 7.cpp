#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 500
void countFrequency(char *ciphertext, int freq[256]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isprint(ch)) {  
            freq[(int)ch]++;
        }
    }
}
void printFrequencies(int freq[256]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0 && isprint(i)) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}
void decryptMessage(char *ciphertext, char *substitution) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isprint(ch)) {
            if (substitution[(int)ch] != '\0') {
                putchar(substitution[(int)ch]);
            } else {
                putchar(ch); 
            }
        } else {
            putchar(ch);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[MAX_LENGTH] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                                  " (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                                  " ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                                  " (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[256] = {0};
    countFrequency(ciphertext, freq);
    printFrequencies(freq);
    char substitution[256] = {0};
    substitution['‡'] = 'E';  
    substitution[';'] = 'T';  
    substitution['*'] = 'H'; 
    substitution['5'] = 'O';  
    substitution['8'] = 'N';  
    substitution['4'] = 'R';  
    substitution['6'] = 'I';  
    printf("Decrypted message:\n");
    decryptMessage(ciphertext, substitution);
    return 0;
}

