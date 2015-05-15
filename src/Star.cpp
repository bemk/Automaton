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
        // TODO Auto-generated constructor stub
        this->start_at = START_NULL;
        this->stop_at = END_INFINITE;

}

Star::~Star()
{
        // TODO Auto-generated destructor stub
}

bool Star::isOfType(char c)
{
        return (c == '*') ? true : false;
}

Symbol* Star::allocateType()
{
        return (Symbol*) new Star();
}
