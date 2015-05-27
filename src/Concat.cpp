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
        this->concatenated = false;

}

Concat::~Concat()
{
}

size_t Concat::build_grammar(string* rule, size_t location)
{
        this->location = location;
        return 1;
}

extern bool verbose;

bool Concat::isOfType(char c)
{
        if (c == '.' && verbose) {
                cerr << "Setting concat" << endl;
        }
        return (c == '.');
}

void Concat::do_concatenate()
{
        if (this->concatenated) {
                return;
        }
        this->concatenated = true;
        Symbol* previous = get_ll_prev();
        Symbol* next = get_ll_next();

        if (next == NULL || previous == NULL) {
                cerr << "concat without sufficient context @" << this->location
                     << endl;
                exit(-1);
        }
        if (previous->get_ll_prev()) {
                previous->get_ll_prev()->set_ll_next(this);
                set_ll_prev(previous->get_ll_prev());
        }
        previous->set_ll_prev(NULL);
        previous->set_ll_next(NULL);

        next->set_ll_prev(NULL);

        setLeft(previous);
        setRight(next);
        set_ll_next(NULL);
        set_ll_prev(NULL);

        Symbol* parent = previous->getParent();

        if (parent) {
                this->setParent(parent);
                if (parent->getLeft() == previous) {
                        parent->setLeft(this);
                }
                if (parent->getRight() == previous) {
                        parent->setRight(this);
                }
        }

        next->setParent(this);
        previous->setParent(this);

        this->getRight()->do_concatenate();
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
