#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using Rail Fence Cipher
void encrypt(char *message, int rails) {
    int messageLen = strlen(message);
    char railFence[rails][messageLen];
    int i, j;
    
    // Initialize rail fence matrix
    for (i = 0; i < rails; i++) {
        for (j = 0; j < messageLen; j++) {
            railFence[i][j] = '\0';
        }
    }
    
    int row = 0;
    int direction = 0; // 0: down, 1: up
    
    // Fill the rail fence matrix
    for (i = 0; i < messageLen; i++) {
        railFence[row][i] = message[i];
        
        if (row == 0)
            direction = 0;
        else if (row == rails - 1)
            direction = 1;
        
        if (direction == 0)
            row++;
        else
            row--;
    }
    
    // Print the encrypted message
    printf("Encrypted Message: ");
    for (i = 0; i < rails; i++) {
        for (j = 0; j < messageLen; j++) {
            if (railFence[i][j] != '\0')
                printf("%c", railFence[i][j]);
        }
    }
    printf("\n");
}

// Function to decrypt a message using Rail Fence Cipher
void decrypt(char *message, int rails) {
    int messageLen = strlen(message);
    char railFence[rails][messageLen];
    int i, j;
    
    // Initialize rail fence matrix
    for (i = 0; i < rails; i++) {
        for (j = 0; j < messageLen; j++) {
            railFence[i][j] = '\0';
        }
    }
    
    int row = 0;
    int direction = 0; // 0: down, 1: up
    
    // Fill the rail fence matrix
    for (i = 0; i < messageLen; i++) {
        railFence[row][i] = '*'; // Placeholder character
        
        if (row == 0)
            direction = 0;
        else if (row == rails - 1)
            direction = 1;
        
        if (direction == 0)
            row++;
        else
            row--;
    }
    
    // Fill the rail fence matrix with the message characters
    int index = 0;
    for (i = 0; i < rails; i++) {
        for (j = 0; j < messageLen; j++) {
            if (railFence[i][j] == '*' && index < messageLen) {
                railFence[i][j] = message[index++];
            }
        }
    }
    
    // Print the decrypted message
    printf("Decrypted Message: ");
    row = 0;
    direction = 0;
    for (i = 0; i < messageLen; i++) {
        printf("%c", railFence[row][i]);
        
        if (row == 0)
            direction = 0;
        else if (row == rails - 1)
            direction = 1;
        
        if (direction == 0)
            row++;
        else
            row--;
    }
    printf("\n");
}

int main() {
    char message[] = "HELLO";
    int rails = 3; // Number of rails

    printf("Original Message: %s\n", message);

    // Encrypt the message
    encrypt(message, rails);

    // Decrypt the message
    decrypt(message, rails);

    return 0;
}
