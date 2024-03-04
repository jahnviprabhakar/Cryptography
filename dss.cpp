#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Helper function to compute modular exponentiation (a^b mod m)
uint64_t mod_exp(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1)
            result = (result * a) % m;
        b >>= 1;
        a = (a * a) % m;
    }
    return result;
}

// Helper function to compute modular multiplicative inverse (a^(-1) mod m)
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    uint64_t m0 = m, t, q;
    uint64_t x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Helper function to check if a number is prime
int is_prime(uint64_t n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (uint64_t i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

// Helper function to generate a prime number
uint64_t generate_prime(uint64_t min, uint64_t max) {
    uint64_t p;
    srand(time(NULL)); // Seed the random number generator
    p = (rand() % (max - min + 1)) + min;
    while (!is_prime(p)) {
        p = (rand() % (max - min + 1)) + min;
    }
    return p;
}

// DSA Key generation
void dsa_keygen(uint64_t *p, uint64_t *q, uint64_t *g, uint64_t *x, uint64_t *y) {
    uint64_t min = 10000; // Minimum value for p
    uint64_t max = 99999; // Maximum value for p
    *q = generate_prime(2, 10); // Choose q (a prime number)
    *p = generate_prime(min, max); // Choose p (a prime number)
    *g = mod_exp(*q + 1, (*p - 1) / (*q), *p); // Compute g
    *x = rand() % (*q - 1) + 1; // Choose x (private key)
    *y = mod_exp(*g, *x, *p); // Compute y (public key)
}

// DSA Signature generation
void dsa_sign(uint64_t p, uint64_t q, uint64_t g, uint64_t x, uint64_t y, uint64_t k, uint64_t *r, uint64_t *s, uint64_t hash) {
    uint64_t k_inv, k_inv_mod_q;
    do {
        do {
            *r = mod_exp(g, k, p) % q;
        } while (*r == 0);
        k_inv = mod_inverse(k, q);
        k_inv_mod_q = k_inv % q;
        *s = (k_inv_mod_q * (hash + x * (*r))) % q;
    } while (*s == 0);
}

// DSA Signature verification
int dsa_verify(uint64_t p, uint64_t q, uint64_t g, uint64_t y, uint64_t r, uint64_t s, uint64_t hash) {
    uint64_t w, u1, u2, v;
    if (r < 0 || r >= q || s < 0 || s >= q)
        return 0;
    w = mod_inverse(s, q);
    u1 = (hash * w) % q;
    u2 = (r * w) % q;
    v = ((mod_exp(g, u1, p) * mod_exp(y, u2, p)) % p) % q;
    return v == r;
}

int main() {
    uint64_t p, q, g, x, y; // Public parameters
    uint64_t k = 5; // Secret key
    uint64_t r, s; // Signature components
    uint64_t hash = 12345; // Hash of the message to be signed

    // Generate DSA keys
    dsa_keygen(&p, &q, &g, &x, &y);

    printf("Generated values:\n");
    printf("p = %llu\n", p);
    printf("q = %llu\n", q);
    printf("g = %llu\n", g);
    printf("x = %llu\n", x);
    printf("y = %llu\n", y);

    // Sign the message
    dsa_sign(p, q, g, x, y, k, &r, &s, hash);
    printf("Generated signature:\n");
    printf("r = %llu\n", r);
    printf("s = %llu\n", s);

    // Verify the signature
    int verified = dsa_verify(p, q, g, y, r, s, hash);

    if (verified)
        printf("Signature verified successfully.\n");
    else
        printf("Signature verification failed.\n");

    return 0;
}
