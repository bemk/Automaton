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

        Symbol* prev = this->get_ll_prev();
        Symbol* dPrev = prev->get_ll_prev();

        dPrev->set_ll_next(this);
        this->set_ll_prev(dPrev);

        prev->set_ll_prev(NULL);
        prev->set_ll_next(NULL);

        this->setLeft(prev);
        prev->setParent(this);

        return 1;
}

Quantifier::~Quantifier()
{
}

bool Quantifier::isOfType(char c)
{
        return false;
}

Symbol* Quantifier::allocateType()
{
        cerr << "Generic quantifier should never be found!!!" << endl;
        return NULL;
}

