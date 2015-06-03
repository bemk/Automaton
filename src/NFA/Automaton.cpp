/*
 * Automaton.cpp
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#include "../include/Automaton.h"
#include <cstdlib>

using namespace std;

namespace NFA {

int unique_id_alloc = 0;

Automaton::Automaton(size_t location, string name)
{
        this->location = location;
        this->name = name;
        this->transitions = vector<Transition*>();
        this->incomming = vector<Transition*>();
        this->unique_id = unique_id_alloc++;

        if (unique_id_alloc < 0) {
                cerr << "Integer overflow!!!!!!" << endl;
                exit(-9001);
        }
}

Automaton::~Automaton()
{
        // TODO Auto-generated destructor stub
}

void Automaton::add_transition(char name, Automaton* dest)
{
        if (dest == NULL) {
                return;
        }

        size_t i = 0;
        Transition* t = this->transitions[i];

        for (; i < this->transitions.size(); i++, t = this->transitions[i]) {
                if (t->get_symbol() == name && t->get_dest() == dest) {
                        return;
                }
        }

        Transition* transition = new Transition(this->location, name, this,
                        dest);

        this->transitions.push_back(transition);
        dest->add_incomming(t);

        return;
}

void Automaton::add_epsilon(Automaton* dest)
{
        for (size_t i = 0; i < this->transitions.size(); i++) {
                if (this->transitions[i]->get_dest() == dest) {
                        return;
                }
        }

        Transition* t = new Transition(this->location, '\0', this, dest);
        t->set_epsylon(true);

        transitions.push_back(t);
        dest->add_incomming(t);

        return;
}

} /* namespace NFA */
