#include <stdio.h>
#include <ctype.h>
void caesarCipher(char *text, int k) {
    char ch;
    int i = 0;
    k = k % 26;
    while (text[i] != '\0') {
        ch = text[i];
        if (isupper(ch)) {
            ch = ((ch - 'A' + k) % 26) + 'A';
        }
        else if (islower(ch)) {
            ch = ((ch - 'a' + k) % 26) + 'a';
        }
        text[i] = ch;
        i++;
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value (k): ");
    scanf("%d", &k);
    caesarCipher(text, k);
    printf("Encrypted message: %s", text);

    return 0;
}

