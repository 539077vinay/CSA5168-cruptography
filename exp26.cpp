#include <stdio.h>
#include <stdint.h>

// Function to calculate gcd (used for finding modular inverse)
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular exponentiation (base^exp) % mod
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        base = (base * base) % mod;  // Square the base
        exp = exp / 2;
    }
    return result;
}

// Extended Euclidean Algorithm to find modular inverse of e mod phi_n
uint64_t mod_inverse(uint64_t e, uint64_t phi_n) {
    int64_t t = 0, newt = 1;
    int64_t r = phi_n, newr = e;
    while (newr != 0) {
        uint64_t quotient = r / newr;
        uint64_t temp_t = t;
        uint64_t temp_r = r;
        
        t = newt;
        newt = temp_t - quotient * newt;

        r = newr;
        newr = temp_r - quotient * newr;
    }
    if (r > 1) {
        return 0; // e is not invertible
    }
    if (t < 0) {
        t += phi_n;
    }
    return t;
}

// RSA Key Generation
void rsa_keygen(uint64_t p, uint64_t q, uint64_t* n, uint64_t* e, uint64_t* d) {
    // Calculate modulus n = p * q
    *n = p * q;

    // Calculate phi(n) = (p - 1) * (q - 1)
    uint64_t phi_n = (p - 1) * (q - 1);

    // Choose a public exponent e such that gcd(e, phi_n) = 1
    *e = 3;
    while (gcd(*e, phi_n) != 1) {
        (*e)++;
    }

    // Calculate private key d (modular inverse of e mod phi(n))
    *d = mod_inverse(*e, phi_n);
}

// RSA Encryption: C = (M^e) % n
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n) {
    return mod_exp(message, e, n);
}

// RSA Decryption: M = (C^d) % n
uint64_t rsa_decrypt(uint64_t ciphertext, uint64_t d, uint64_t n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    uint64_t p = 61;     // First prime number
    uint64_t q = 53;     // Second prime number
    uint64_t n, e, d;

    // Generate RSA keys
    rsa_keygen(p, q, &n, &e, &d);

    printf("RSA Key Generation Complete:\n");
    printf("Public Key: (n = %llu, e = %llu)\n", n, e);
    printf("Private Key: d = %llu\n\n", d);

    // Simulate private key leak and regenerate keys without changing modulus n
    printf("Simulating private key leak...\n");
    rsa_keygen(p, q, &n, &e, &d);  // Trying to regenerate e and d without changing n

    printf("New Key Pair Generated (without changing n):\n");
    printf("Public Key: (n = %llu, e = %llu)\n", n, e);
    printf("Private Key: d = %llu\n", d);

    // Encrypt and decrypt a message
    uint64_t message = 42; // Example plaintext message
    uint64_t ciphertext = rsa_encrypt(message, e, n);
    uint64_t decrypted = rsa_decrypt(ciphertext, d, n);

    printf("\nOriginal Message: %llu\n", message);
    printf("Encrypted Message: %llu\n", ciphertext);
    printf("Decrypted Message: %llu\n", decrypted);

    return 0;
}

