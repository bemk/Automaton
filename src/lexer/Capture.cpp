/*
 * Capture.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: Thomas Moors & Bart Kuivenhoven
 */

#include "../include/Capture.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

extern bool verbose;

namespace Lexer {

Capture::Capture(Lexer *p) : Token(p)
{
    this->str_length = 0;
}

size_t Capture::build_grammar(string *rule, size_t location)
{
    this->location = location;
    int depth_cnt = 0;
    int cnt = 1;
    for (string::iterator it = rule->begin(); it != rule->end(); ++it, cnt++) {
        char c = *it;
        switch (c) {
        case '(':
            if (depth_cnt++ != 0) {
                this->text.push_back(c);
            }
            break;
        case ')':
            depth_cnt--;
            if (depth_cnt > 0) {
                this->text.push_back(c);
            } else if (depth_cnt < 0) {
                cerr << "Found ')' at char "
                        << location
                        << " but was not matched!"
                        << endl;
                exit(-4);
            } else {
                goto end_of_loop;
            }
            break;
        default:
            if (depth_cnt != 0) {
                this->text.push_back(c);
            }
            break;

        }
    }
    cerr << "Expected ')' but was not found!" << endl;
    cerr << "( at " << location << " was not matched!" << endl;
    exit(-2);

    end_of_loop:

    this->str_length = cnt;
    if (verbose) {
        /* Dump the parsed input */
        cout << "Captured: " << this->text << endl;
    }

    Lexer *nodes = new Lexer(location);
    nodes->build_grammar(&this->text);

    Token *symbols = nodes->get_tokens()->omit_starter();

    if (symbols != NULL) {
        this->setRight(symbols);
        symbols->setParent(this);
    } else {
        cerr << "Error at " << location << endl;
    }

    /* Make sure there are no undefined pointers after deleting nodes */
    symbols->set_parser(this->parser);

    delete nodes;
    return this->length();
}

Capture::~Capture()
{
}

size_t Capture::length()
{
    return this->str_length;
}

bool Capture::isOfType(char c)
{
    return (c == '(' || c == ')');
}

Token* Capture::allocateType()
{
    Token *s = (Token*) new Capture(this->parser);
    if (s == NULL) {
        std::cerr << "NULL POINTER ALLOCATED" << endl;
        exit(-1);
    }
    return s;
}

void Capture::build_automata()
{
    if (this->automata.size()) {
        return;
    }

    stringstream name_start;
    stringstream name_end;

    name_start << "q_" << this->location << "_0";
    name_end << "q_" << this->location << "_1";

    NFA::State *start = new NFA::State(this->location, name_start.str());
    NFA::State *end = new NFA::State(this->location, name_end.str());

    start->add_epsilon(this->getRight()->get_start_symbol());
    this->getRight()->get_accept_symbol()->add_epsilon(end);
    this->start = start;
    this->end = end;

    this->automata.push_back(start);
    this->automata.push_back(end);

    return;
}

}
