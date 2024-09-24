#include <stdio.h>
#include <stdint.h>

// Function to calculate modular exponentiation (base^exp) % mod
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// RSA Encryption: C = (M^e) % n
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n) {
    return mod_exp(message, e, n);
}

// Simulating the brute-force attack by precomputing encryptions for all possible alphabetic characters
void brute_force_rsa_attack(uint64_t e, uint64_t n, uint64_t ciphertext) {
    printf("Brute-forcing ciphertext: %llu\n", ciphertext);
    for (uint64_t message = 0; message <= 25; ++message) {
        uint64_t encrypted = rsa_encrypt(message, e, n);
        if (encrypted == ciphertext) {
            printf("Ciphertext %llu corresponds to plaintext letter: '%c'\n", ciphertext, 'A' + message);
            return;
        }
    }
    printf("No match found for the ciphertext\n");
}

int main() {
    // Bob's public RSA key (for simplicity, these are small values; in practice, n and e should be large)
    uint64_t n = 3233;    // Modulus (product of two primes, p = 61, q = 53)
    uint64_t e = 17;      // Public exponent
    
    // Alice's plaintext message represented as characters (e.g., "HELLO")
    char message[] = "HELLO";
    
    printf("Encrypting message: %s\n", message);
    
    // Encrypt each character in the message
    for (int i = 0; message[i] != '\0'; ++i) {
        uint64_t plaintext = message[i] - 'A';  // Convert 'A' = 0, 'B' = 1, ..., 'Z' = 25
        uint64_t ciphertext = rsa_encrypt(plaintext, e, n);
        printf("Plaintext letter: '%c' -> Encrypted: %llu\n", message[i], ciphertext);
        
        // Simulate brute-force attack
        brute_force_rsa_attack(e, n, ciphertext);
    }

    return 0;
}

