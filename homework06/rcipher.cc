#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

RCipher::RCipher() {
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    rotate_string(cipher_alpha, 13);
    smile = new CipherCheshire;
    smile->cipher_alpha = cipher_alpha;
}

// -------------------------------------------------------
