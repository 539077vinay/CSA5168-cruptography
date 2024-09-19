#include <stdio.h>
#include <stdint.h>
uint32_t gcd_extended(uint32_t a, uint32_t b, uint32_t *x, uint32_t *y);
uint32_t mod_inverse(uint32_t e, uint32_t phi);
void factorize(uint32_t n, uint32_t *p, uint32_t *q);

int main() {
    uint32_t e = 31;
    uint32_t n = 3599;
    uint32_t p, q, phi, d;

    factorize(n, &p, &q);

    phi = (p - 1) * (q - 1);
    d = mod_inverse(e, phi);
    printf("Public Key: (e = %u, n = %u)\n", e, n);
    printf("Private Key: (d = %u)\n", d);
    printf("Factors: p = %u, q = %u\n", p, q);

    return 0;
}
void factorize(uint32_t n, uint32_t *p, uint32_t *q) {
    for (uint32_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
}
uint32_t gcd_extended(uint32_t a, uint32_t b, uint32_t *x, uint32_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    uint32_t x1, y1;
    uint32_t gcd = gcd_extended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
uint32_t mod_inverse(uint32_t e, uint32_t phi) {
    uint32_t x, y;
    uint32_t gcd = gcd_extended(e, phi, &x, &y);

    if (gcd != 1) {
        printf("Modular inverse does not exist.\n");
        return 0;
    } else {
        return (x % phi + phi) % phi; 
    }
}

