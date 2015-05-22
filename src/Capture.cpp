/*
 * Capture.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Capture.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Capture::Capture(Parser* p) :
                Symbol(p)
{
        this->str_length = 0;
}

extern bool verbose;

size_t Capture::build_grammar(string* rule, size_t location)
{
        this->location = location;
        int depth_cnt = 0;
        int cnt = 1;
        for (string::iterator it = rule->begin(); it != rule->end();
                        ++it, cnt++) {
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
                                cerr << "Found ')' at char " << location
                                     << " but was not matched!" << endl;
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

        Parser* nodes = new Parser(location);
        nodes->build_grammar(&this->text);

        Symbol* symbols = nodes->get_symbols();

        if (symbols != NULL) {
                this->setLeft(symbols);
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
        switch (c) {
        case '(':
        case ')':
                return true;
        default:
                return false;
        }
}

Symbol* Capture::allocateType()
{
        Symbol* s = (Symbol*) new Capture(this->parser);
        if (s == NULL) {
                std::cerr << "NULL POINTER ALLOCATED" << endl;
                exit(-1);
        }
        return s;
}
