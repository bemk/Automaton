/*
 * Concat.cpp
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#include "include/Concat.h"
#include <cstdlib>

using namespace std;

Concat::Concat() :
                Symbol()
{
        this->set_concatenation(false);

}

Concat::~Concat()
{
}

size_t Concat::build_grammar(string* rule, size_t location)
{
        this->text.push_back('.');

        return 1;
}

bool Concat::isOfType(char c)
{
        if (c == '.') {
                cerr << "Setting concat" << endl;
        }
        return (c == '.');
}

Symbol* Concat::allocateType()
{
        Symbol* s = new Concat();

        if (s == NULL) {
                cerr << " Unable to allocate new Concat!" << endl;
                exit(-1);
        }
        return s;
}
