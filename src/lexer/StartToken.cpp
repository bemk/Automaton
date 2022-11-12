/*
 * StartSymbol.cpp
 *
 *  Created on: 20 May 2015
 *      Author: bemk
 */

#include "../include/StartToken.h"

namespace Lexer {

StartToken::StartToken(Lexer *p) : Token(p)
{
}

StartToken::~StartToken()
{
}

Token* StartToken::omit_starter()
{
    Token *next = this->get_ll_next();
    next->set_ll_prev(NULL);
    next->setParent(this->getParent());
    delete this;
    return next;
}

}
