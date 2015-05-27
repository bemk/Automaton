/*
 * StartSymbol.cpp
 *
 *  Created on: 20 May 2015
 *      Author: bemk
 */

#include "include/StartSymbol.h"

StartSymbol::StartSymbol(Parser* p) : Symbol(p)
{
}

StartSymbol::~StartSymbol()
{
}

Symbol* StartSymbol::ommit_starter()
{
        Symbol* next = this->get_ll_next();
        next->set_ll_prev(NULL);
        delete this;
        return next;
}
