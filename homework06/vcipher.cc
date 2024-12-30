#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
struct KCipher::CipherCheshire {
    vector<string> book;
    int page = 0;
};

VCipher::VCipher() {
    // init and make key eally long
    ksmile = new CipherCheshire;
    string page;
    for (int i=0; i<(int)MAX_LENGTH; i++) { page += 'a'; }
    ksmile->book.push_back(page);
}

VCipher::VCipher(string key) {
    // init check for valid key 
    if (key.empty()) {
        cerr << "Invalid Running key: " << key << endl;
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<(int)key.length(); i++) {
        if (!isalpha(key[i])) {
            cerr << "Error: not a valid Vigenere key word" << endl;
            exit(EXIT_FAILURE);
        }
    }
    string key_rep;    
    ksmile = new CipherCheshire;
    for (int i=0; i<(int)(MAX_LENGTH/(key.length()+1)); i++) {
        key_rep += key;
    }
    // cout << key_rep << endl;
    ksmile->book.push_back(key_rep);
}
// -------------------------------------------------------

