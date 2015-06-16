/*
 * State.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/State.h"
#include <sstream>

using namespace std;

namespace DFA {

static int unique_id_alloc = 0;

State::State(size_t location, string name) :
                NFA::State(location, name)
{
        stringstream name_str;
        name_str << "q_" << unique_id_alloc++;

        this->name = name_str.str();
}

State::~State()
{
        // TODO Auto-generated destructor stub
}

} /* namespace DFA */
