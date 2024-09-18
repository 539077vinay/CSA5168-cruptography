#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
void vigenereEncrypt(char *plaintext, const char *key) { 
 int keyLength = strlen(key); 
 int i,textLength = strlen(plaintext); 
 for (i = 0; i < textLength; i++) { 
 if (isalpha(plaintext[i])) {
 char keyChar = key[i % keyLength]; 
 int keyShift = isupper(keyChar) ? keyChar - 'A' : keyChar - 'a'; 
 if (isupper(plaintext[i])) { 
 plaintext[i] = (plaintext[i] - 'A' + keyShift) % 26 + 'A';  } else { 
 plaintext[i] = (plaintext[i] - 'a' + keyShift) % 26 + 'a';  } 
 } 
 } 
} 
void vigenereDecrypt(char *ciphertext, const char *key) {  int keyLength = strlen(key); 
 int i,textLength = strlen(ciphertext); 
 for ( i = 0; i < textLength; i++) { 
 if (isalpha(ciphertext[i])) { 
 char keyChar = key[i % keyLength]; 
 int keyShift = isupper(keyChar) ? keyChar - 'A' : keyChar - 'a'; 
 if (isupper(ciphertext[i])) { 
 ciphertext[i] = (ciphertext[i] - 'A' - keyShift + 26) % 26 + 'A';  } else { 
 ciphertext[i] = (ciphertext[i] - 'a' - keyShift + 26) % 26 + 'a';  } 
 } 
 } 
} 
int main() { 
 char plaintext[100]; 
 char key[100];
 printf("Enter plaintext: "); 
 fgets(plaintext, sizeof(plaintext), stdin); 
 plaintext[strcspn(plaintext, "\n")] = '\0'; 
 printf("Enter key: "); 
 fgets(key, sizeof(key), stdin); 
 key[strcspn(key, "\n")] = '\0'; 
 vigenereEncrypt(plaintext, key); 
 printf("Encrypted text: %s\n", plaintext); 
 vigenereDecrypt(plaintext, key); 
 printf("Decrypted text: %s\n", plaintext); 
 return 0; 
} 
