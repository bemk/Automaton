/*
 * Star.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "include/Star.h"

using namespace std;

Star::Star() :
                Quantifier()
{
        this->start_at = START_NULL;
        this->stop_at = END_INFINITE;

}

Star::~Star()
{
}

bool Star::isOfType(char c)
{
        return (c == '*') ? true : false;
}

Symbol* Star::allocateType()
{
        Symbol* s = new Star();
        if (s == NULL) {
                std::cerr << "Unable to allocate new star descriptor"
                          << std::endl;
                exit(-1);
        }
        return s;
}
