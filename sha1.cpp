#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> // Include the standard library header for malloc

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

// Circular left shift macro
#define SHA1_ROTL(bits, word) (((word) << (bits)) | ((word) >> (32 - (bits))))

// SHA-1 initialization constants
const uint32_t SHA1_INIT_CONSTANTS[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

// SHA-1 message schedule constants
const uint32_t SHA1_MESSAGE_SCHEDULE_CONSTANTS[4] = {
    0x5A827999,
    0x6ED9EBA1,
    0x8F1BBCDC,
    0xCA62C1D6
};

// Function prototypes
void sha1(const unsigned char *input, size_t len, uint32_t *hash);

// Main function
int main() {
    const char *text = "Hello, world!";
    size_t text_len = strlen(text);
    uint32_t hash[SHA1_DIGEST_SIZE / sizeof(uint32_t)];

    sha1((const unsigned char *)text, text_len, hash);

    printf("SHA-1 Hash: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE / sizeof(uint32_t); i++) {
        printf("%08x", hash[i]);
    }
    printf("\n");

    return 0;
}

// SHA-1 hash function
void sha1(const unsigned char *input, size_t len, uint32_t *hash) {
    uint32_t h[5];
    uint64_t bit_len = len * 8;
    size_t padding_len = ((len + 8) / SHA1_BLOCK_SIZE + 1) * SHA1_BLOCK_SIZE;
    unsigned char *padded_input = (unsigned char *)malloc(padding_len);
    if (padded_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(padded_input, input, len);
    padded_input[len] = 0x80;
    memset(padded_input + len + 1, 0, padding_len - len - 1 - 8);
    for (int i = 0; i < 8; i++) {
        padded_input[padding_len - 8 + i] = (bit_len >> ((7 - i) * 8)) & 0xFF;
    }
    h[0] = SHA1_INIT_CONSTANTS[0];
    h[1] = SHA1_INIT_CONSTANTS[1];
    h[2] = SHA1_INIT_CONSTANTS[2];
    h[3] = SHA1_INIT_CONSTANTS[3];
    h[4] = SHA1_INIT_CONSTANTS[4];
    for (size_t i = 0; i < padding_len; i += SHA1_BLOCK_SIZE) {
        uint32_t w[80];
        memcpy(w, padded_input + i, SHA1_BLOCK_SIZE);
        for (int j = 16; j < 80; j++) {
            w[j] = SHA1_ROTL(1, w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]);
        }
        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];
        for (int j = 0; j < 80; j++) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = SHA1_MESSAGE_SCHEDULE_CONSTANTS[0];
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = SHA1_MESSAGE_SCHEDULE_CONSTANTS[1];
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = SHA1_MESSAGE_SCHEDULE_CONSTANTS[2];
            } else {
                f = b ^ c ^ d;
                k = SHA1_MESSAGE_SCHEDULE_CONSTANTS[3];
            }
            uint32_t temp = SHA1_ROTL(5, a) + f + e + k + w[j];
            e = d;
            d = c;
            c = SHA1_ROTL(30, b);
            b = a;
            a = temp;
        }
        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
    }
    for (int i = 0; i < SHA1_DIGEST_SIZE / sizeof(uint32_t); i++) {
        hash[i] = h[i];
    }
    free(padded_input);
}
