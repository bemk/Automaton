/*
 * Plus.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "include/Plus.h"

Plus::Plus(Parser* p) :
                Quantifier(p)
{
        this->start_at = START_ONE;
        this->stop_at = END_INFINITE;
        this->text = "plus";
}

Plus::~Plus()
{
}

bool Plus::isOfType(char c)
{
        return (c == '+') ? true : false;
}

Symbol* Plus::allocateType()
{
        Symbol* s = new Plus(this->parser);

        if (s == NULL) {
                std::cerr << "Unable to allocate Plus descriptor" << std::endl;
                exit(-1);
        }
        return s;
}
