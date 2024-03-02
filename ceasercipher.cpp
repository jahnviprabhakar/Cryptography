#include <stdio.h>
void caesar_encrypt(char message[], int key) {
    int i;
    char encrypted_message[100];
    for (i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            encrypted_message[i] = 'a' + (message[i] - 'a' + key) % 26;
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            encrypted_message[i] = 'A' + (message[i] - 'A' + key) % 26;
        } else {
            encrypted_message[i] = message[i]; 
        }
    }
    encrypted_message[i] = '\0';
    printf("Encrypted message: %s\n", encrypted_message);
}
void caesar_decrypt(char message[], int key) {
    caesar_encrypt(message, 26 - key); 
}
int main() {
    char message[100];
    int key;
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key (a number between 1 and 25): ");
    scanf("%d", &key);
    caesar_encrypt(message, key);
    caesar_decrypt(message, key);
    printf("Decrypted message: %s\n", message);
    return 0;
}
