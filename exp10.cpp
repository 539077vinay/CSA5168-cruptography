#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char matrix[SIZE][SIZE]) {
    char predefinedMatrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = predefinedMatrix[i][j];
        }
    }
}
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') {
        ch = 'I'; 
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void preprocessMessage(char message[], char processedMessage[]) {
    int len = 0;
    for (int i = 0; i < strlen(message); i++) {
        
        if (isalpha(message[i])) {
            processedMessage[len++] = toupper(message[i]);
        }
    }

    
    for (int i = 0; i < len; i += 2) {
        if (i + 1 == len) { 
            processedMessage[len++] = 'X';
        } else if (processedMessage[i] == processedMessage[i + 1]) { 
            for (int j = len; j > i + 1; j--) {
                processedMessage[j] = processedMessage[j - 1];
            }
            processedMessage[i + 1] = 'X';
            len++;
        }
    }
    processedMessage[len] = '\0'; 
}

void encrypt(char message[], char matrix[SIZE][SIZE]) {
    int row1, col1, row2, col2;

    for (int i = 0; i < strlen(message); i += 2) {
        findPosition(matrix, message[i], &row1, &col1);
        findPosition(matrix, message[i + 1], &row2, &col2);

        
        if (row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + 1) % SIZE], matrix[row2][(col2 + 1) % SIZE]);
        }
       
        else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + 1) % SIZE][col1], matrix[(row2 + 1) % SIZE][col2]);
        }
        
        else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
}

int main() {
    char matrix[SIZE][SIZE];
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char processedMessage[100];

   
    createMatrix(matrix);
    preprocessMessage(message, processedMessage);

    printf("Encrypted Message: ");
    encrypt(processedMessage, matrix);
    printf("\n");

    return 0;
}

