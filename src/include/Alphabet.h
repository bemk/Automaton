/*
 * Alphabet.h
 *
 *  Created on: 15 May 2015
 *      Author: Thomas Moors & Bart Kuivenhoven
 */

#ifndef SRC_ALPHABET_H_
#define SRC_ALPHABET_H_

#include <iostream>
#include <vector>

class Alphabet {
private:
        std::vector<char> alpha;
        std::string str;

protected:
        Alphabet();
        virtual ~Alphabet();

public:
        static Alphabet* get_alphabet();
        std::string* get_string();
        void push_char(char c);
        size_t get_size();

        int get_char_index(char c);

};

#endif /* SRC_ALPHABET_H_ */
