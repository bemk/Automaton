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
        this->states = map<char, vector<IntState*>*>();
        this->epsilon_state = vector<IntState*>();
}

IntState::~IntState()
{
        for (int idx = 0; idx < Alphabet::get_alphabet()->get_size(); idx++) {
                char key = (*Alphabet::get_alphabet()->get_string())[idx];
                vector<IntState*>* state = this->states[key];
                delete state;
        }
        this->states.clear();
}

void IntState::build_error_transitions()
{
        Alphabet* alphabet = Alphabet::get_alphabet();
        for (int idx = 0; idx < alphabet->get_size(); idx++) {
                char c = (*alphabet->get_string())[idx];
                this->states[c] = new vector<IntState*>();
                this->states[c]->push_back(this->get_error_state());
        }

}

IntState* IntState::get_error_state()
{
        if (errorState == NULL) {
                errorState = new IntState(Alphabet::get_alphabet()->get_size());
        }

        return errorState;
}

void IntState::add_transition(IntState* dest, char c)
{
        if ((*this->states[c])[0] == this->get_error_state()) {
                (*this->states[c])[0] = dest;
                return;
        }
        this->states[c]->push_back(dest);
}

} /* namespace DFA */
