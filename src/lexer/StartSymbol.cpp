/*
 * StartSymbol.cpp
 *
 *  Created on: 20 May 2015
 *      Author: bemk
 */

#include "../include/StartSymbol.h"

namespace lexer {

StartSymbol::StartSymbol(Lexer* p) :
                Token(p)
{
}

StartSymbol::~StartSymbol()
{
}

Token* StartSymbol::omit_starter()
{
        Token* next = this->get_ll_next();
        next->set_ll_prev(NULL);
        next->setParent(this->getParent());
        delete this;
        return next;
}

}
