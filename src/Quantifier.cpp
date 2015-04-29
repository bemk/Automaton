/*
 * Quantifier.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Quantifier.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Quantifier::Quantifier() :
                Symbol()
{
        /* If no quantifier is given, default to exactly one */
        start_at = START_ONE;
        stop_at = END_ONE;
}

size_t Quantifier::build_grammar(string* rule, size_t location)
{
        this->location = location;
        char c = rule->at(0);
        switch (c) {
        case '*':
                start_at = START_NULL;
                stop_at = END_INFINITE;
                break;
        case '+':
                start_at = START_ONE;
                stop_at = END_INFINITE;
                break;
        case '?':
                start_at = START_NULL;
                stop_at = END_ONE;
                break;
        default:
                break;
        }
        return 1;
}

Quantifier::~Quantifier()
{
        // TODO Auto-generated destructor stub
}

bool Quantifier::isOfType(char c)
{
        switch (c) {
        case '*':
        case '?':
        case '+':
                return true;
        default:
                return false;
        }
}

Symbol* Quantifier::allocateType()
{
        Symbol* s = (Symbol*)new Quantifier();
        if (s == NULL) {
                std::cerr << "NULL POINTER ALLOCATED" << endl;
                exit(-1);
        }
        return s;
}

