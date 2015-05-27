/*
 * Concat.cpp
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#include "include/Concat.h"
#include <cstdlib>

using namespace std;

Concat::Concat(Parser* p) :
                Symbol(p)
{
        this->set_concatenation(false);
        this->text = ".";

}

Concat::~Concat()
{
}

size_t Concat::build_grammar(string* rule, size_t location)
{
        this->location = location;
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
        Symbol* s = new Concat(this->parser);

        if (s == NULL) {
                cerr << " Unable to allocate new Concat!" << endl;
                exit(-1);
        }
        return s;
}
