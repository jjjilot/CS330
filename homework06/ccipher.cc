#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

CCipher::CCipher() {
    smile = new CipherCheshire;
    smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
}

CCipher::CCipher(int shift) {
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    if (shift>0) {
    rotate_string(cipher_alpha, shift);
    smile = new CipherCheshire;
    smile->cipher_alpha = cipher_alpha;
    } else {
        cerr << "Error: Caesar cipher is less than 0" << endl;
        exit(EXIT_FAILURE);
    }
}

// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void CCipher::rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    rot = rot%in_str.length();
    for (int i=0; i<(int)rot/2; i++) {
        char temp = in_str[i];
        in_str[i] = in_str[rot-i-1];
        in_str[rot-i-1] = temp;
    }
    for (int i=0; i<(int)(in_str.length()-rot)/2; i++) {
        int ind = i + rot;
        char temp = in_str[ind];
        in_str[ind] = in_str[in_str.length()-i-1];
        in_str[in_str.length()-i-1] = temp;
    }
    for (int i=0; i<(int)in_str.length()/2; i++) {
        char temp = in_str[i];
        in_str[i] = in_str[in_str.length()-i-1];
        in_str[in_str.length()-i-1] = temp;
    }
}
