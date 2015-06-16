/*
 * IntState.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/IntState.h"
#include "../include/Alphabet.h"
#include "../include/NFA/State.h"

using namespace std;
namespace DFA {

IntState::IntState(size_t alphabet_size)
{
        this->states = map<char, vector<NFA::State*>*>();
        this->epsilon_state = vector<NFA::State*>();

        this->startstate = false;
        this->endstate = false;
}

IntState::~IntState()
{
        for (int idx = 0; idx < Alphabet::get_alphabet()->get_size(); idx++) {
                char key = (*Alphabet::get_alphabet()->get_string())[idx];
                vector<NFA::State*>* state = this->states[key];
                delete state;
        }
        this->states.clear();
}

void IntState::build_error_transitions()
{
}

IntState* IntState::get_error_state()
{
        if (errorState == NULL) {
                errorState = new IntState(Alphabet::get_alphabet()->get_size());
        }

        return errorState;
}

void IntState::add_transition(NFA::State* dest, char c)
{
        vector<NFA::State*>* mapped = this->states[c];

        for (int idx = 0; idx < mapped->size(); idx++) {
                if (mapped->at(idx) == dest) {
                        return;
                }
        }

        mapped->push_back(dest);
}

bool IntState::compare(IntState* cmp)
{
#warning Function needs implementation
        return false;
}

bool IntState::has_e_transition(NFA::State* destination)
{
        for (int i = 0; i < this->destinations.size(); i++) {
                if (this->destinations[i] == destination) {
                        return true;
                }
        }
        return false;
}

bool IntState::put_e_transition(NFA::State* destination)
{
        if (this->has_e_transition(destination)) {
                return false;
        }

        this->destinations.push_back(destination);

        return true;
}

bool IntState::get_endstate()
{
        return this->endstate;
}

void IntState::set_endstate()
{
        this->endstate = true;
}

} /* namespace DFA */
