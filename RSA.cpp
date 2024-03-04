#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate modulo inverse using extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}

// Function to generate RSA keys
void generate_keys(int p, int q, int *e, int *d, int *n) {
    // Calculate n
    *n = p * q;

    // Calculate totient of n
    int phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    *e = 2; // Starting with a small prime number
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    // Calculate d (modular multiplicative inverse of e modulo phi)
    *d = mod_inverse(*e, phi);
}

// Function to perform RSA encryption
uint64_t encrypt(uint64_t plaintext, int e, int n) {
    return fmod(pow(plaintext, e), n);
}

// Function to perform RSA decryption
uint64_t decrypt(uint64_t ciphertext, int d, int n) {
    return fmod(pow(ciphertext, d), n);
}

int main() {
    int p = 61; // Prime number 1
    int q = 53; // Prime number 2
    int e, d, n; // RSA parameters
    uint64_t plaintext = 123456; // Plain text message
    uint64_t encrypted, decrypted; // Encrypted and decrypted message

    // Generate RSA keys
    generate_keys(p, q, &e, &d, &n);

    // Encrypt the message
    encrypted = encrypt(plaintext, e, n);
    printf("Encrypted: %lu\n", encrypted);

    // Decrypt the message
    decrypted = decrypt(encrypted, d, n);
    printf("Decrypted: %lu\n", decrypted);

    return 0;
}
