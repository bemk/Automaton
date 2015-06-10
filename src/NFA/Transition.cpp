/*
 * Transition.cpp
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#include "../include/NFA/Transition.h"
#include <iostream>

namespace NFA {

void Transition::init(size_t location, char symbol, State* source, State* dest)
{
        this->location = location;
        this->symbol = symbol;
        this->source = source;
        this->dest = dest;
        this->epsilon = false;

        return;
}

Transition::Transition(size_t location, char symbol, State* source, State* dest)
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

void Transition::set_source(State* source)
{
        this->source = source;
        return;
}

State* Transition::get_source()
{
        return this->source;
}

void Transition::set_dest(State* dest)
{
        this->dest = dest;
        return;
}

State* Transition::get_dest()
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

bool Transition::get_epsilon()
{
        if (this == NULL) {
                std::cerr << "Some crazy magic is going on here!" << std::endl;
        }
        return this->epsilon;
}

void Transition::set_epsilon(bool epsilon)
{
        this->epsilon = epsilon;
}

} /* namespace NFA */
