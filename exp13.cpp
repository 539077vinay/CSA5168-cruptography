#include <stdio.h>
#include <string.h>
#define MOD 26
int mod26(int x) {
    return (x % MOD + MOD) % MOD;
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
int determinant(int matrix[2][2]) {
    return mod26(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}
void matrixInverse(int matrix[2][2], int inverse[2][2]) {
    int det = determinant(matrix);
    int detInverse = modInverse(det, MOD);

    if (detInverse == -1) {
        printf("Matrix is not invertible\n");
        return;
    }
    inverse[0][0] = mod26(detInverse * matrix[1][1]);
    inverse[1][1] = mod26(detInverse * matrix[0][0]);
    inverse[0][1] = mod26(-detInverse * matrix[0][1]);
    inverse[1][0] = mod26(-detInverse * matrix[1][0]);
}
void findKeyMatrix(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int A[2][2] = { {plaintext[0][0], plaintext[0][1]}, {plaintext[1][0], plaintext[1][1]} };
    int B[2][2] = { {ciphertext[0][0], ciphertext[0][1]}, {ciphertext[1][0], ciphertext[1][1]} };
    int A_inv[2][2];
    int temp[2][2];
    matrixInverse(A, A_inv);

    temp[0][0] = mod26(B[0][0] * A_inv[0][0] + B[0][1] * A_inv[1][0]);
    temp[0][1] = mod26(B[0][0] * A_inv[0][1] + B[0][1] * A_inv[1][1]);
    temp[1][0] = mod26(B[1][0] * A_inv[0][0] + B[1][1] * A_inv[1][0]);
    temp[1][1] = mod26(B[1][0] * A_inv[0][1] + B[1][1] * A_inv[1][1]);

    key[0][0] = temp[0][0];
    key[0][1] = temp[0][1];
    key[1][0] = temp[1][0];
    key[1][1] = temp[1][1];
}
int charToNum(char c) {
    return c - 'a';
}
char numToChar(int num) {
    return num + 'a';
}
void matrixMultiply(int matrix[2][2], int vector[2], int result[2]) {
    result[0] = mod26(matrix[0][0] * vector[0] + matrix[0][1] * vector[1]);
    result[1] = mod26(matrix[1][0] * vector[0] + matrix[1][1] * vector[1]);
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
    int plaintext[2][2] = { {charToNum('h'), charToNum('e')}, {charToNum('l'), charToNum('l')} };
    int ciphertext[2][2] = { {charToNum('k'), charToNum('p')}, {charToNum('o'), charToNum('n')} };
    int key[2][2];
    findKeyMatrix(plaintext, ciphertext, key);
    
    printf("Recovered key matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    int key_inv[2][2];
    matrixInverse(key, key_inv);
    char message[] = "helloworld";
    char ciphertext_text[100];
    char decrypted_text[100];

    encryptMessage(message, key, ciphertext_text);
    printf("Encrypted message: %s\n", ciphertext_text);

    decryptMessage(ciphertext_text, key_inv, decrypted_text);
    printf("Decrypted message: %s\n", decrypted_text);

    return 0;
}

