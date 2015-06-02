#include <iostream>
#include <string.h>
using namespace std;

void set_indexes(char* message, int message_size, int* left, int* right,
                 int* alphabet_size, int* key_size) {
    int middle = message_size / 2;

    int i = middle - 1;
    int power10 = 1;
    while (message[i] != '~') {
        *key_size += (message[i] - '0') * power10;
        power10 *= 10;
        i --;
    }
    *left = i;

    i = middle;
    while (message[i] != '~') {
        *alphabet_size *= 10;
        *alphabet_size += (message[i] - '0');
        i ++;
    }
    *right = i;
}

char* set_alphabet(char *message, int message_size, int *right, int alphabet_size) {
    char* alphabet = new char[alphabet_size];
    for (int i = 0; i < alphabet_size; i++) {
        *right += 1;
        *right %= message_size;
        alphabet[i] = message[*right];
    }
    *right += 1;
    *right %= message_size;
    return alphabet;
}

int* set_key(char* message, int *left, int key_size, char* alphabet, int alphabet_size) {
    int* key = new int[key_size];
    for(int i = key_size - 1; i >= 0; i--) {
        *left -= 1;
        char current = message[*left];
        for (int j = 0; j < alphabet_size; j++) {
            if (alphabet[j] == current) {
                key[i] = j;
                break;
            }
        }
    }
    return key;
}

char* set_decrypted(char* message, int message_size, int left, int right,
                    char* alphabet, int alphabet_size, int* key, int key_size) {
    int offset = (right >= left) ? (right - left + 1) : (left - right + 1);
    char* decrypted = new char[message_size - offset + 2];
    decrypted[message_size - offset + 1] = '\0';
    int i, j, index;
    for (i = 0; i < message_size - offset + 1; i++) {
        char current = message[right];
        for (j = 0; j < alphabet_size; j++) {
            if (current == alphabet[j]) {
                index = (j + alphabet_size - key[i % key_size]) % alphabet_size;
                break;
            }
        }
        decrypted[i] = alphabet[index];
        right ++;
        right %= message_size;
    }
    return decrypted;
}

char* decrypt(char* message) {
    int message_size = strlen(message);

    int left;
    int right;
    int alphabet_size = 0;
    int key_size = 0;
    set_indexes(message, message_size, &left, &right, &alphabet_size, &key_size);
    char* alphabet = set_alphabet(message, message_size, &right, alphabet_size);
    int* key = set_key(message, &left, key_size, alphabet, alphabet_size);
    char* decrypted = set_decrypted(message, message_size, left, right, alphabet, alphabet_size, key, key_size);

    delete[] alphabet;
    delete[] key;
    return decrypted;
}

int main() {
    char* example1 = decrypt("rc hscesi tcrest~410~thisaecr .rcese");
    cout << example1 << "\n";

    char* example2 = decrypt("fl k.ccfsIolskv.~312~ .Ifrckslovelvo");
    cout << example2 << "\n";

    char* example3 = decrypt("o?uin uw?stutnfwat?~413~orwa? thfuisnnrsiu");
    cout << example3 << "\n";


    delete[] example1;
    delete[] example2;
    delete[] example3;

    cin.get();
    return 0;
}
