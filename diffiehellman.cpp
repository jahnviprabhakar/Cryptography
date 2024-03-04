#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define P 23 // Prime number
#define G 5  // Generator

// Function to calculate modulo power (a^b mod m)
uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to perform Diffie-Hellman key exchange
void diffie_hellman(uint64_t p, uint64_t g, uint64_t *private_key, uint64_t *public_key) {
    *private_key = rand() % (p - 1) + 1; // Random private key
    *public_key = mod_pow(g, *private_key, p); // Calculate public key
}

int main() {
    uint64_t alice_private_key, bob_private_key;
    uint64_t alice_public_key, bob_public_key;
    uint64_t alice_shared_secret, bob_shared_secret;

    // Alice generates her key pair
    diffie_hellman(P, G, &alice_private_key, &alice_public_key);

    // Bob generates his key pair
    diffie_hellman(P, G, &bob_private_key, &bob_public_key);

    // Alice calculates shared secret
    alice_shared_secret = mod_pow(bob_public_key, alice_private_key, P);

    // Bob calculates shared secret
    bob_shared_secret = mod_pow(alice_public_key, bob_private_key, P);

    // Both Alice and Bob should have the same shared secret
    printf("Alice's Shared Secret: %lu\n", alice_shared_secret);
    printf("Bob's Shared Secret: %lu\n", bob_shared_secret);

    return 0;
}
