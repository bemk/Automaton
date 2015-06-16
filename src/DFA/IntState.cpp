/*
 * IntState.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/IntState.h"
#include "../include/Alphabet.h"
#include "../include/NFA/State.h"
#include "../include/DFA/State.h"
#include <cstdlib>

using namespace std;
namespace DFA {

IntState::IntState(size_t alphabet_size)
{
        this->states = map<char, vector<NFA::State*>*>();

        this->startstate = false;
        this->endstate = false;

        this->local_alphabet = vector<char>();
        this->DFA_State = NULL;
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

void IntState::add_transition(NFA::State* dest, char c)
{
        vector<NFA::State*>* mapped = this->states[c];
        if (mapped == NULL) {
                mapped = new vector<NFA::State*>();
                this->states[c] = mapped;
        }

        this->local_alphabet.push_back(c);

        for (int idx = 0; idx < mapped->size(); idx++) {
                if (mapped->at(idx) == dest) {
                        return;
                }
        }

        mapped->push_back(dest);
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

void IntState::build_int_states()
{
        /* For each letter in local alphabet */
        for (int idx = 0; idx < local_alphabet.size(); idx++) {

                /* Make intermediate state */
                IntState* state = new IntState(
                                Alphabet::get_alphabet()->get_size());

                char c = local_alphabet[idx];

                /* and for each coupled NFA state */
                vector<NFA::State*>* vec = this->states[c];

                for (int i = 0; i < vec->size(); i++) {
                        /* Add your own letters to the new alphabet */
                        if (vec->at(i)->get_closure() != NULL) {
                                continue;
                        }
                        vec->at(i)->set_closure(state);
                        vec->at(i)->build_closure_state(state);
                }

                /* Now for each letter in the alphabet, build intermediate tree */
                state->build_int_states();
        }
}

State* IntState::build_dfa_state()
{
        if (this->DFA_State != NULL) {
                return this->DFA_State;
        }

        DFA_State = new State(0, "");
        if (this->endstate) {
                ((NFA::State*) DFA_State)->set_end_state(true);
        }
        for (int idx = 0; idx < this->local_alphabet.size(); idx++) {
                char c = this->local_alphabet[idx];

                vector<NFA::State*>* vec = this->states[c];
                if (vec == NULL || vec->at(0) == NULL) {
                        cerr << "NULL pointer!!!" << endl;
                        exit(-9004);
                }
                NFA::State* NFA_state = vec->at(0);
                DFA::State* tmp_state = NFA_state->get_closure()
                                ->build_dfa_state();
                if (tmp_state == NULL) {
                        cerr << "Oh noes!!!" << endl;
                }
                DFA_State->add_transition(c, tmp_state);

        }

        return DFA_State;
}

} /* namespace DFA */
