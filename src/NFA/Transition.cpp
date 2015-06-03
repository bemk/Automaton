/*
 * Transition.cpp
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#include "../include/Transition.h"

namespace NFA {

void Transition::init(size_t location, char symbol, Automaton* source,
                Automaton* dest)
{
        this->location = location;
        this->symbol = symbol;
        this->source = source;
        this->dest = dest;
        this->epsylon = false;

        return;
}

Transition::Transition(size_t location, char symbol, Automaton* source,
                Automaton* dest)
{
        init(location, symbol, source, dest);
}

Transition::Transition(size_t location)
{
        init(location, '\0', NULL, NULL);
}

Transition::~Transition()
{
        // TODO Auto-generated destructor stub
}

void Transition::set_source(Automaton* source)
{
        this->source = source;
        return;
}

Automaton* Transition::get_source()
{
        return this->source;
}

void Transition::set_dest(Automaton* dest)
{
        this->dest = dest;
        return;
}

Automaton* Transition::get_dest()
{
        return this->dest;
}

void Transition::set_symbol(char symbol)
{
        this->symbol = symbol;
        return;
}

char Transition::get_symbol()
{
        return this->symbol;
}

} /* namespace NFA */
