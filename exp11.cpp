#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int num_letters = 25;
    unsigned long long total_keys = factorial(num_letters);
    unsigned long long row_col_factor = factorial(5) * factorial(5);
    unsigned long long unique_keys = total_keys / row_col_factor;
    double log_total_keys = log2((double)total_keys);
    double log_unique_keys = log2((double)unique_keys);
    printf("Total possible Playfair keys (ignoring duplicates): %llu\n", total_keys);
    printf("Total possible Playfair keys (approximate power of 2): 2^%.2f\n", log_total_keys);

    printf("Effectively unique Playfair keys (accounting for symmetry): %llu\n", unique_keys);
    printf("Effectively unique Playfair keys (approximate power of 2): 2^%.2f\n", log_unique_keys);

    return 0;
}

