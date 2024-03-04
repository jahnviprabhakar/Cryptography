#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using Vigenère Cipher
void encrypt(char *message, char *key) {
    int i, j;
    int messageLen = strlen(message);
    int keyLen = strlen(key);

    for (i = 0, j = 0; i < messageLen; i++, j++) {
        if (j == keyLen)
            j = 0;
        
        if (isalpha(message[i])) {
            int shift = key[j] - 'A';
            if (islower(message[i]))
                message[i] = 'a' + (message[i] - 'a' + shift) % 26;
            else
                message[i] = 'A' + (message[i] - 'A' + shift) % 26;
        }
    }
}

// Function to decrypt a message using Vigenère Cipher
void decrypt(char *message, char *key) {
    int i, j;
    int messageLen = strlen(message);
    int keyLen = strlen(key);

    for (i = 0, j = 0; i < messageLen; i++, j++) {
        if (j == keyLen)
            j = 0;
        
        if (isalpha(message[i])) {
            int shift = key[j] - 'A';
            if (islower(message[i]))
                message[i] = 'a' + (message[i] - 'a' - shift + 26) % 26;
            else
                message[i] = 'A' + (message[i] - 'A' - shift + 26) % 26;
        }
    }
}

int main() {
    char message[] = "HELLO";
    char key[] = "KEY";

    printf("Original Message: %s\n", message);

    // Encrypt the message
    encrypt(message, key);
    printf("Encrypted Message: %s\n", message);

    // Decrypt the message
    decrypt(message, key);
    printf("Decrypted Message: %s\n", message);

    return 0;
}
