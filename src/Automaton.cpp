/*
 * Automaton.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Automaton.h"

using namespace std;


Automaton::Automaton(string* rule)
{
        this->internal_string = new string();
}

Automaton::~Automaton()
{
        // TODO Auto-generated destructor stub
}

int Automaton::parse(string* line, int max_depth = 5)
{
	return 0;
}
