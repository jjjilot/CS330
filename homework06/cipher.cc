#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
    // TODO: Implement this default constructor
    smile = new CipherCheshire;
    smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
}

/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
    // TODO: Implement this constructor
    if (is_valid_alpha(cipher_alpha)) {
    smile = new CipherCheshire;
    smile->cipher_alpha = cipher_alpha;
    } else {
        cerr << "Invalid cipher alphabet/key: " << cipher_alpha << endl;
        exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
Cipher::~Cipher()
{
    // TODO: Implement this constructor
    delete smile;
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    // implement alg from class
    cout << "Encrypting...";
    string retStr;
    // TODO: Finish this function
    for (int i=0; i<(int)raw.length(); i++) {
        int ins_ind = tolower(raw[i])-'a';
        // cout << "raw[i]: " << raw[i] << ", ins_ind: " << ins_ind << "\n";
        char ins_val;
        if (raw[i] != ' ') {
            ins_val = smile->cipher_alpha[ins_ind];
        } else { ins_val = ' '; }
        if (isupper(raw[i])) { ins_val = toupper(ins_val); }
        retStr += ins_val;
    }
    // cout << retStr << endl;
    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    // reverse encrpy alg
    string retStr;
    cout << "Decrypting...";
    // TODO: Finish this function
    for (int i=0; i<(int)enc.length(); i++) {
        int ins_ind = (int)find_pos(smile->cipher_alpha, tolower(enc[i]));
        char ins_val;
        if (enc[i] != ' ') {
            ins_val = ins_ind + 'a';
        } else { ins_val = ' ';}
        if (isupper(enc[i])) { ins_val = toupper(ins_val); }
        retStr += ins_val;
    }
    // cout << retStr << endl;
    cout << "Done" << endl;

    return retStr;

}
// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int Cipher::find_pos(string alpha, char c)
{
    unsigned int pos = 0;

    // TODO: You will likely need this function. Finish it.
    for (int i=0; i<26; i++) {
        if (alpha[i]==c) { pos=i; }
    }

    return (unsigned int)pos;
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool Cipher::is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}

