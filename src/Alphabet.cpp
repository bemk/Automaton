/*
 * Alphabet.cpp
 *
 *  Created on: 15 May 2015
 *      Author: bemk
 */

#include "include/Alphabet.h"

using namespace std;

Alphabet *alphabet = NULL;

Alphabet::Alphabet()
{
    alpha = vector<char>();
}

Alphabet::~Alphabet()
{
}

extern bool verbose;

void Alphabet::push_char(char c)
{
    for (size_t i = 0; i < alpha.size(); i++) {
        if (alpha[i] == c) {
            return;
        }
    }

    alpha.push_back(c);
    str.push_back(c);
    if (verbose) {
        cout << "Added " << c << " to the alphabet!" << endl;
    }
}

Alphabet* Alphabet::get_alphabet()
{
    if (alphabet == NULL) {
        alphabet = new Alphabet();
    }

    return alphabet;
}

string* Alphabet::get_string()
{
    return &str;
}

size_t Alphabet::get_size()
{
    return this->alpha.size();
}

/* Convert char to array index */
int Alphabet::get_char_index(char c)
{
    int i = 0;
    for (; i < this->alpha.size(); i++) {
        if (this->alpha[i] == c) {
            return i;
        }
    }
    return -1;
}
