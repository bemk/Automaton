/*
 * Transition.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/Transition.h"

namespace DFA {

Transition::Transition(size_t location, char character, NFA::State* source,
                NFA::State* dest) :
                NFA::Transition(location, character, source, dest)
{
}

Transition::~Transition()
{
// TODO Auto-generated destructor stub
}

} /* namespace DFA */
