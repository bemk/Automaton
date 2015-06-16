/*
 * State.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/State.h"
#include "../include/Alphabet.h"
#include <sstream>

using namespace std;

namespace DFA {

static int unique_id_alloc = 0;

static State* global_error_state = NULL;

State::State(size_t location, string name) :
                NFA::State(location, name)
{
        stringstream name_str;
        name_str << "q_" << unique_id_alloc++;

        this->name = name_str.str();

        error_state = false;
        this->map_transitions = map<char, State*>();

        Alphabet* alpha = Alphabet::get_alphabet();

        for (int idx = 0; idx < alpha->get_string()->size(); idx++) {
                char c = alpha->get_string()->at(idx);

                this->map_transitions[c] = this->get_error();
        }
}

State::~State()
{
}

void State::add_transition(char c, State* s)
{
        this->map_transitions[c] = s;
}

void State::set_error_state()
{
        this->error_state = true;
}

State* State::get_error()
{
        if (global_error_state != NULL) {
                global_error_state = new State(0, "ERROR");
        }
        return global_error_state;
}

} /* namespace DFA */
