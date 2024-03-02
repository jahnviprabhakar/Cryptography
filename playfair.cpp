#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // Include the stdlib.h header file

#define SIZE 5
char keyMatrix[SIZE][SIZE];

void prepareKeyMatrix(char key[]) {
    int i, j, k, flag = 0, *visited = (int *)calloc(26, sizeof(int));
    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'j') key[i] = 'i'; 
        if (!visited[key[i] - 'a']) {
            keyMatrix[flag / SIZE][flag % SIZE] = key[i];
            visited[key[i] - 'a'] = 1;
            flag++;
        }
    }
    for (k = 0; k < 26; k++) {
        if (k != ('j' - 'a') && !visited[k]) {
            keyMatrix[flag / SIZE][flag % SIZE] = k + 'a';
            flag++;
        }
    }
    free(visited); // Free the memory allocated by calloc
}

void findPosition(char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char message[]) {
    int i, len = strlen(message), p1row, p1col, p2row, p2col;
    for (i = 0; i < len; i += 2) {
        findPosition(message[i], &p1row, &p1col);
        findPosition(message[i + 1], &p2row, &p2col);
        if (p1row == p2row) {
            message[i] = keyMatrix[p1row][(p1col + 1) % SIZE];
            message[i + 1] = keyMatrix[p2row][(p2col + 1) % SIZE];
        } else if (p1col == p2col) {
            message[i] = keyMatrix[(p1row + 1) % SIZE][p1col];
            message[i + 1] = keyMatrix[(p2row + 1) % SIZE][p2col];
        } else {
            message[i] = keyMatrix[p1row][p2col];
            message[i + 1] = keyMatrix[p2row][p1col];
        }
    }
}

void decrypt(char message[]) {
    int i, len = strlen(message), p1row, p1col, p2row, p2col;
    for (i = 0; i < len; i += 2) {
        findPosition(message[i], &p1row, &p1col);
        findPosition(message[i + 1], &p2row, &p2col);
        if (p1row == p2row) {
            message[i] = keyMatrix[p1row][(p1col - 1 + SIZE) % SIZE];
            message[i + 1] = keyMatrix[p2row][(p2col - 1 + SIZE) % SIZE];
        } else if (p1col == p2col) {
            message[i] = keyMatrix[(p1row - 1 + SIZE) % SIZE][p1col];
            message[i + 1] = keyMatrix[(p2row - 1 + SIZE) % SIZE][p2col];
        } else {
            message[i] = keyMatrix[p1row][p2col];
            message[i + 1] = keyMatrix[p2row][p1col];
        }
    }
}

int main() {
    char key[SIZE * SIZE], message[100];
    printf("Enter the key (without spaces, only alphabets, max 25 letters): ");
    scanf("%s", key);
    printf("Enter the message to encrypt: ");
    scanf("%s", message);
    prepareKeyMatrix(key);
    encrypt(message);
    printf("Encrypted message: %s\n", message);
    decrypt(message);
    printf("Decrypted message: %s\n", message);
    return 0;
}
