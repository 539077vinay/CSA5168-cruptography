#include <stdio.h>
#include <ctype.h>
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void affineEncrypt(char *plaintext, int a, int b) {
    char ch;
    int i = 0;

    while (plaintext[i] != '\0') {
        ch = plaintext[i];

        if (isupper(ch)) {
            plaintext[i] = ((a * (ch - 'A') + b) % 26) + 'A';
        } else if (islower(ch)) {
            plaintext[i] = ((a * (ch - 'a') + b) % 26) + 'a';
        }

        i++;
    }
}
void affineDecrypt(char *ciphertext, int a, int b) {
    char ch;
    int i = 0;
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Decryption is not possible. 'a' has no modular inverse.\n");
        return;
    }
    while (ciphertext[i] != '\0') {
        ch = ciphertext[i];

        if (isupper(ch)) {
            ciphertext[i] = ((a_inv * ((ch - 'A') - b + 26)) % 26) + 'A';
        } else if (islower(ch)) {
            ciphertext[i] = ((a_inv * ((ch - 'a') - b + 26)) % 26) + 'a';
        }

        i++;
    }
}
int main() {
    char text[100];
    int a, b, choice;
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter value of a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);
    printf("Enter your choice (1 for Encryption, 2 for Decryption): ");
    scanf("%d", &choice);
    if (choice == 1) {  
        affineEncrypt(text, a, b);
        printf("Encrypted message: %s", text);
    } else if (choice == 2) {
        affineDecrypt(text, a, b);
        printf("Decrypted message: %s", text);
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}

