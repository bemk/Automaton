/*
 * Automaton.cpp
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#include "../include/Automaton.h"

using namespace std;

namespace NFA {

Automaton::Automaton(size_t location, string name)
{
        this->location = location;
        this->name = name;
}

Automaton::~Automaton()
{
        // TODO Auto-generated destructor stub
}

} /* namespace NFA */
