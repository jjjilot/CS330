#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
struct KCipher::CipherCheshire {
    vector<string> book;
    int page = 0;
};

KCipher::KCipher() {
    // init and make key lots of a's (index 0)
    ksmile = new CipherCheshire;
    string page;
    for (int i=0; i<(int)MAX_LENGTH; i++) { page += 'a'; }
    ksmile->book.push_back(page);
}

KCipher::KCipher(string page1) {
    // init and check valid page
    if (page1.empty()) {
        cerr << "Invalid Running key: " << page1 << endl;
        exit(EXIT_FAILURE);
    }    
    ksmile = new CipherCheshire;
    ksmile->book.push_back(page1);
}

KCipher::~KCipher() {
    delete ksmile;
}

void KCipher::set_id(unsigned int page_in=0) {
    ksmile->page = page_in;
}

void KCipher::add_key(string page) {
    // add key to book and check valid key
    for (int i=0; page[i]; i++) {
        if (page[i] != ' ' && !isalpha(page[i])) {
            cerr << "Invalid Running key: " << page << endl;
            exit(EXIT_FAILURE);
        }
    }
    ksmile->book.push_back(page);
}

string KCipher::encrypt(string raw) {
    // cout << "Encrypting..." << endl;
    string retStr;
    // Check valid book index
    // cout << ksmile->page << endl;
    // cout << ksmile->book.size() << endl;

    // check valid page index
    if (ksmile->page > (int)ksmile->book.size()-1) {
        cerr << "Warning: invalid id: " << ksmile->page << endl;
        exit(EXIT_FAILURE);
    }
    
    // Index into book and remove spaces from key
    // Check key has only valid characters
    string cipher_alpha = ksmile->book[ksmile->page];
    string cipher_orig = cipher_alpha;
    int j = 0;
    for (int i=0; cipher_alpha[i]; i++) {
        if (isalpha(cipher_alpha[i])) { 
            cipher_alpha[j++] = cipher_alpha[i]; 
        } else if (cipher_alpha[i] != ' ') {
            cerr << "Invalid Running key: " << cipher_orig << endl;
            exit(EXIT_FAILURE);
        }
    }
    cipher_alpha.resize(j);
    // cout << cipher_alpha << endl;

    // Check valid key length (non-space characters)
    int spaces = 0;
    string raw_strip;
    for (int i=0; raw[i]; i++) {
        if (raw[i] == ' ') { 
            spaces++;
        } else { 
            raw_strip += raw[i]; 
        }
    }
    if ((int)raw.length()-spaces > j) {
        cerr << "Invalid Running key: " << cipher_orig << endl;
        exit(EXIT_FAILURE);
    }

    // implement vigenere/rk algorithm
    int ns_ptr = 0;
    for (int i=0; i<(int)raw.length(); i++) {
        char ins_val;
        string alpha = "abcdefghijklmnopqrstuvwxyz";
        if (raw[i] == ' ') { ins_val = ' '; } 
        else {
            int rot = tolower(raw_strip[ns_ptr]) - 'a';
            rotate_string(alpha, rot);
            ins_val = alpha[cipher_alpha[ns_ptr++] - 'a'];
            if (isupper(raw[i])) { ins_val = toupper(ins_val); }
        }
        retStr += ins_val;
    }
    // cout << "enc: "<< retStr << endl;
    // cout << "Done" << endl;
    return retStr;
}

string KCipher::decrypt(string enc) {
    // TODO
    // cout << "Decrypting..." << endl;
    string retStr;

    // vigenere/rk but backwards basically
    string cipher_alpha = ksmile->book[ksmile->page];
    string cipher_strip;
    for (int i=0; cipher_alpha[i]; i++) {
        if (cipher_alpha[i] != ' ') { 
            cipher_strip += cipher_alpha[i]; 
        }
    }
    // cout << cipher_strip << endl;
    string enc_strip;
    for (int i=0; enc[i]; i++) {
        if (enc[i] != ' ') { 
            enc_strip += enc[i]; 
        }
    }

    int ns_ptr = 0;
    int ins_ind;
    char ins_val;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i<(int)enc.length(); i++) {
        if (enc[i] == ' ') { ins_val = ' '; }
        else {
            ins_ind = (tolower(enc_strip[ns_ptr])-'a') - (tolower(cipher_strip[ns_ptr])-'a');
            ins_val = alpha[(ins_ind+26)%26];
            if (isupper(enc[i])) { ins_val = toupper(ins_val); }
            ns_ptr++;
        }
        retStr += ins_val;
    }
    // cout << "dec: " << retStr << endl;
    // cout << "Done" << endl;
    return retStr;
}

// -------------------------------------------------------

