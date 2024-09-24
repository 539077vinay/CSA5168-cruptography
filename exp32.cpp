#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Example DSA parameters (simplified for demonstration purposes)
#define P 23     // Small prime for modulus
#define Q 11     // Small prime for subgroup order
#define G 4      // Generator in subgroup

// Function to compute modular exponentiation (base^exp) % mod
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to compute the modular inverse of a number a mod m
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// DSA signature generation
void dsa_sign(uint64_t private_key, uint64_t k, uint64_t message_hash, uint64_t* r, uint64_t* s) {
    // Calculate r = (g^k mod p) mod q
    *r = mod_exp(G, k, P) % Q;

    // Calculate s = k^(-1) * (message_hash + private_key * r) mod q
    uint64_t k_inv = mod_inverse(k, Q);
    *s = (k_inv * (message_hash + private_key * (*r))) % Q;
}

// DSA signature verification
int dsa_verify(uint64_t public_key, uint64_t message_hash, uint64_t r, uint64_t s) {
    // Calculate w = s^(-1) mod q
    uint64_t w = mod_inverse(s, Q);

    // Calculate u1 = (message_hash * w) mod q
    uint64_t u1 = (message_hash * w) % Q;

    // Calculate u2 = (r * w) mod q
    uint64_t u2 = (r * w) % Q;

    // Calculate v = ((g^u1 * public_key^u2) mod p) mod q
    uint64_t v = ((mod_exp(G, u1, P) * mod_exp(public_key, u2, P)) % P) % Q;

    // Signature is valid if v == r
    return v == r;
}

// Recover the private key if k is reused
void recover_private_key(uint64_t message_hash1, uint64_t message_hash2, uint64_t r, uint64_t s1, uint64_t s2, uint64_t q) {
    if (s1 == s2) {
        printf("Signatures cannot be identical for different messages.\n");
        return;
    }

    // Compute private key using the equation: x = ((s1 - s2)^-1 * (message_hash1 - message_hash2)) mod q
    uint64_t s_diff = (s1 - s2 + q) % q;
    uint64_t h_diff = (message_hash1 - message_hash2 + q) % q;
    uint64_t s_diff_inv = mod_inverse(s_diff, q);

    uint64_t private_key = (s_diff_inv * h_diff) % q;
    printf("Recovered private key: %llu\n", private_key);
}

int main() {
    // Private key and public key (private key x, public key = g^x mod p)
    uint64_t private_key = 7;  // Example private key
    uint64_t public_key = mod_exp(G, private_key, P);

    // Message hashes (simulating signing two different messages)
    uint64_t message_hash1 = 5;
    uint64_t message_hash2 = 9;

    // Same random k value (which is bad for DSA)
    uint64_t k = 3;

    // Signature variables
    uint64_t r1, s1, r2, s2;

    // Sign both messages using the same k
    dsa_sign(private_key, k, message_hash1, &r1, &s1);
    dsa_sign(private_key, k, message_hash2, &r2, &s2);

    // Print the signatures
    printf("Message 1 Signature: (r1 = %llu, s1 = %llu)\n", r1, s1);
    printf("Message 2 Signature: (r2 = %llu, s2 = %llu)\n", r2, s2);

    // Verify signatures
    if (dsa_verify(public_key, message_hash1, r1, s1)) {
        printf("Message 1 signature is valid.\n");
    } else {
        printf("Message 1 signature is invalid.\n");
    }

    if (dsa_verify(public_key, message_hash2, r2, s2)) {
        printf("Message 2 signature is valid.\n");
    } else {
        printf("Message 2 signature is invalid.\n");
    }

    // Recover the private key since k was reused
    if (r1 == r2) {
        recover_private_key(message_hash1, message_hash2, r1, s1, s2, Q);
    } else {
        printf("Error: Different r values, k is not reused.\n");
    }

    return 0;
}

