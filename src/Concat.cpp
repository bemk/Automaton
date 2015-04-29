/*
 * Concat.cpp
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#include "include/Concat.h"

Concat::Concat() : Symbol()
{
        // TODO Auto-generated constructor stub

}

Concat::~Concat()
{
        // TODO Auto-generated destructor stub
}

bool Concat::isOfType(char c) {
        return (c == '.') ? true : false;
}
