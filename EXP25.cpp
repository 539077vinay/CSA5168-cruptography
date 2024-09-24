#include <stdio.h>
#include <stdint.h>

// Function to compute the greatest common divisor (GCD) of two numbers
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    uint64_t n = 0;       // The modulus n = p * q (RSA modulus)
    uint64_t e = 0;       // Public exponent e (part of the public key)
    uint64_t P = 0;       // One plaintext block that shares a common factor with n

    // Input RSA modulus (n), public key exponent (e), and plaintext block (P)
    printf("Enter the RSA modulus (n = p * q): ");
    scanf("%llu", &n);
    printf("Enter the public key exponent (e): ");
    scanf("%llu", &e);
    printf("Enter the plaintext block (P) that shares a common factor with n: ");
    scanf("%llu", &P);

    // Calculate gcd(P, n)
    uint64_t factor = gcd(P, n);

    if (factor > 1 && factor < n) {
        printf("The plaintext block shares a common factor with n.\n");
        printf("The factor is: %llu\n", factor);
        printf("We have successfully factored n!\n");

        // Once we have p or q, we can easily factor n
        uint64_t other_factor = n / factor;
        printf("The other factor is: %llu\n", other_factor);

        // Now we can compute phi(n) = (p - 1) * (q - 1)
        uint64_t phi_n = (factor - 1) * (other_factor - 1);
        printf("Euler's totient function phi(n) = %llu\n", phi_n);

        // Optionally, compute the private key (d) if needed (modular inverse of e mod phi(n))
        // This part requires more complex math and libraries like GMP to implement properly

    } else {
        printf("The plaintext block does not share a common factor with n.\n");
    }

    return 0;
}

