/*
 * Concat.cpp
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#include "../include/Concat.h"
#include <cstdlib>
#include <sstream>

using namespace std;

extern bool verbose;

namespace lexer {

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
        set_ll_next (NULL);
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

void Concat::build_automata()
{
        if (automata.size() != 0) {
                return;
        }

        stringstream start_name;
        stringstream end_name;

        start_name << "q_" << location << "_0";
        end_name << "q_" << location << "_1";

        NFA::Automaton* start = new NFA::Automaton(this->location,
                        start_name.str());
        NFA::Automaton* end = new NFA::Automaton(this->location,
                        end_name.str());

        start->add_epsilon(this->getLeft()->get_start_symbol());
        this->getLeft()->get_accept_symbol()->add_epsilon(
                        this->getRight()->get_start_symbol());
        this->getRight()->get_accept_symbol()->add_epsilon(end);

        this->start = start;
        this->end = end;

        this->automata.push_back(start);
        this->automata.push_back(end);

        return;
}

}
