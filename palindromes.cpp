#include <iostream>
#include <string.h>
using namespace std;

bool is_palindrome(char* all_rotations, int start_index, int end_index, char* rotation) {
    bool result = true;
    int middle = (start_index + end_index + 1) / 2;
    for(int i = start_index; i < middle; i++) {
        if (all_rotations[i] != all_rotations[start_index + end_index - i]) {
            result = false;
            break;
        }
        rotation[i - start_index] = all_rotations[i];
        rotation[end_index - i] = all_rotations[i];
    }
    if (result && (end_index - start_index + 1) % 2 == 1) {
        rotation[middle - start_index] = all_rotations[middle];
    }
    return result;
}

void palindrome_rotations(char* word) {
    int length = strlen(word);
    int new_length = length * 2 - 1;
    char* all_rotations = new char[new_length];
    for(int i = 0; i < new_length; i++) {
        all_rotations[i] = word[i % length];
    }

    bool has_palindromes = false;
    char* rotation = new char[length + 1];
    rotation[length] = '\0';
    for(int i = 0; i < length; i++) {
        if (is_palindrome(all_rotations, i, i + length - 1, rotation)) {
            cout << rotation << "\n";
            has_palindromes = true;
        }
    }
    if (! has_palindromes) {
        cout << "NONE" << "\n";
    }
    delete[] rotation;
    delete[] all_rotations;
}


int main() {
    palindrome_rotations("labalaa");
    palindrome_rotations("akawwaka");
    palindrome_rotations("shakira");

    cin.get();
    return 0;
}
