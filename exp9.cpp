#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0}; 
    int i, j, index = 0;
  
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'J' && !used[toupper(key[i]) - 'A']) {
            matrix[index / SIZE][index % SIZE] = toupper(key[i]);
            used[toupper(key[i]) - 'A'] = 1;
            index++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) { 
            matrix[index / SIZE][index % SIZE] = 'A' + i;
            index++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int* row, int* col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decrypt(char message[], char matrix[SIZE][SIZE]) {
    int i, row1, col1, row2, col2;
    
    for (i = 0; i < strlen(message); i += 2) {
        findPosition(matrix, toupper(message[i]), &row1, &col1);
        findPosition(matrix, toupper(message[i+1]), &row2, &col2);

        
        if (row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + SIZE - 1) % SIZE], matrix[row2][(col2 + SIZE - 1) % SIZE]);
        }
       
        else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + SIZE - 1) % SIZE][col1], matrix[(row2 + SIZE - 1) % SIZE][col2]);
        }
       
        else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
}

int main() {
    char key[] = "KEYWORD";  
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char matrix[SIZE][SIZE];

    createMatrix(key, matrix);

    
    printf("Decrypted Message: ");
    decrypt(message, matrix);
    printf("\n");

    return 0;
}

