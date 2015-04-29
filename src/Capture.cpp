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

Capture::Capture() :
                Symbol()
{
        this->quantifier = new Quantifier();
        this->a_length = 0;
        this->nodes = NULL;
}

size_t Capture::build_grammar(string* rule)
{
        int depth_cnt = 0;
        int cnt = 0;
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
                        if (depth_cnt != 0) {
                                this->text.push_back(c);
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
        exit(-2);

        end_of_loop:

        /* Dump the parsed input */
        cout << "Captured: " << this->text << endl;

        nodes = new Parser();
        nodes->build_grammar(&this->text);

        return this->length();
}

Capture::~Capture()
{
        // TODO Auto-generated destructor stub
}

size_t Capture::length()
{
        return this->text.length() + 1;
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
        Symbol* s = (Symbol*)new Capture();
        if (s == NULL) {
                std::cerr << "NULL POINTER ALLOCATED" << endl;
                exit(-1);
        }
        return s;
}
