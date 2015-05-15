/*
 * Plus.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "include/Plus.h"

Plus::Plus() :
                Quantifier()
{
        this->start_at = START_ONE;
        this->stop_at = END_INFINITE;
}

Plus::~Plus()
{
        // TODO Auto-generated destructor stub
}

bool Plus::isOfType(char c)
{
        return (c == '+') ? true : false;
}

Symbol* Plus::allocateType()
{
        return (Symbol*) new Plus();
}
