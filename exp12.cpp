#include <stdio.h>
#include <string.h>
int mod26(int x) {
    return (x % 26 + 26) % 26;
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void matrixMultiply(int matrix[2][2], int vector[2], int result[2]) {
    result[0] = mod26(matrix[0][0] * vector[0] + matrix[0][1] * vector[1]);
    result[1] = mod26(matrix[1][0] * vector[0] + matrix[1][1] * vector[1]);
}
void matrixInverse(int matrix[2][2], int inverse[2][2]) {
    int det = mod26(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    int detInverse = modInverse(det, 26);

    if (detInverse == -1) {
        printf("Matrix is not invertible\n");
        return;
    }
    inverse[0][0] = mod26(detInverse * matrix[1][1]);
    inverse[1][1] = mod26(detInverse * matrix[0][0]);
    inverse[0][1] = mod26(-detInverse * matrix[0][1]);
    inverse[1][0] = mod26(-detInverse * matrix[1][0]);
}
int charToNum(char c) {
    return c - 'a';
}
char numToChar(int num) {
    return num + 'a';
}
void encryptMessage(char* message, int key[2][2], char* ciphertext) {
    int vector[2], result[2];
    int length = strlen(message);
    int idx = 0;

    for (int i = 0; i < length; i += 2) {
        vector[0] = charToNum(message[i]);
        vector[1] = charToNum(message[i+1]);

        matrixMultiply(key, vector, result);

        ciphertext[idx++] = numToChar(result[0]);
        ciphertext[idx++] = numToChar(result[1]);
    }
    ciphertext[idx] = '\0'; 
}
void decryptMessage(char* ciphertext, int key_inv[2][2], char* plaintext) {
    int vector[2], result[2];
    int length = strlen(ciphertext);
    int idx = 0;

    for (int i = 0; i < length; i += 2) {
        vector[0] = charToNum(ciphertext[i]);
        vector[1] = charToNum(ciphertext[i+1]);

        matrixMultiply(key_inv, vector, result);

        plaintext[idx++] = numToChar(result[0]);
        plaintext[idx++] = numToChar(result[1]);
    }
    plaintext[idx] = '\0';
}

int main() {
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";
    if (strlen(message) % 2 != 0) {
        strcat(message, "x");
    }
    int key[2][2] = {{9, 4}, {5, 7}};
    int key_inv[2][2];
    matrixInverse(key, key_inv);
    char ciphertext[100];
    char decryptedtext[100];
    encryptMessage(message, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);
    decryptMessage(ciphertext, key_inv, decryptedtext);
    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}

