/*
 * Quantifier.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Quantifier.h"
#include <iostream>

using namespace std;

Quantifier::Quantifier(string* rule) : Automaton (rule)
{
	char c = rule->at(0);
	switch (c)
	{
	case '*':
		start_at = START_NULL;
		stop_at = END_INFINITE;
		break;
	case '+':
		start_at = START_ONE;
		stop_at = END_INFINITE;
		break;
	case '?':
		start_at = START_NULL;
		stop_at = END_ONE;
		break;
	default:
		break;
	}
}

Quantifier::~Quantifier()
{
        // TODO Auto-generated destructor stub
}

