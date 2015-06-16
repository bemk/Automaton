/*
 * Automaton.cpp
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#include <cstdlib>
#include <sstream>
#include <vector>
#include "../include/NFA/State.h"
#include "../include/DFA/IntState.h"
#include "../include/Alphabet.h"

using namespace std;
extern bool simple_graph;

namespace NFA {

static int unique_id_alloc = 0;

State::State(size_t location, string name)
{
        this->end_state = false;
        this->unique_id = unique_id_alloc++;
        if (unique_id_alloc < 0) {
                cerr << "Integer overflow!!!!!!" << endl;
                exit(-9001);
        }

        if (simple_graph) {
                stringstream name_stream;
                name_stream << "q" << this->unique_id;
                this->name = name_stream.str();
        } else {
                this->name = name;
        }

        this->graphed = false;
        this->location = location;
        this->transitions = vector<Transition*>();
        this->incomming = vector<Transition*>();
        this->int_state = NULL;
}

State::~State()
{
        // TODO Auto-generated destructor stub
}

void State::add_transition(char name, State* dest)
{
        if (dest == NULL) {
                return;
        }

        size_t i = 0;
        Transition* t = NULL;

        for (; i < this->transitions.size(); i++) {
                t = this->transitions[i];
                if (t->get_token() == name && t->get_dest() == dest) {
                        return;
                }
        }

        Transition* transition = new Transition(this->location, name, this,
                        dest);

        this->transitions.push_back(transition);
        dest->add_incomming(transition);

        return;
}

void State::add_epsilon(State* dest)
{
        for (size_t i = 0; i < this->transitions.size(); i++) {
                if (this->transitions[i]->get_dest() == dest) {
                        return;
                }
        }

        Transition* t = new Transition(this->location, '\0', this, dest);
        t->set_epsilon(true);

        transitions.push_back(t);
        dest->add_incomming(t);

        return;
}

bool State::get_dotgraph(string* s)
{
        if (s == NULL || graphed) {
                return false;
        }

        graphed = true;

        bool to_graph = true;
        if (incomming.size() == 1 && transitions.size() == 1) {
                if (incomming[0]->get_epsilon() && transitions[0]->get_epsilon()) {
                        to_graph = false;
                }
        }

        for (size_t i = 0; i < transitions.size(); i++) {
                if (to_graph) {
                        transitions[i]->get_dest()->get_dot_reference(s, &name,
                                        this->transitions[i]->get_epsilon(),
                                        this->transitions[i]->get_token());
                }
                transitions[i]->get_dest()->get_dotgraph(s);
        }

        return true;
}

void State::get_dot_reference(std::string* s, std::string* caller, bool epsylon,
                char input)
{
        if (this->incomming.size() == 1 && this->transitions.size() == 1) {
                if (incomming[0]->get_epsilon() && transitions[0]->get_epsilon()) {
                        transitions[0]->get_dest()->get_dot_reference(s, caller,
                                        true, input);
                        return;
                }
        }

        s->append(*caller);
        s->append(" -> ");
        s->append(this->name);
        s->append(" [ label = \"");
        if (epsylon) {
                s->append("&#949;");
        } else {
                if (input != 0) {
                        s->push_back(input);
                }
        }
        s->append("\" ];\n");
}

string* State::get_name()
{
        return &this->name;
}

void State::set_end_state(bool end_state)
{
        this->end_state = end_state;
}

bool State::get_end_state()
{
        return this->end_state;
}

void State::build_closure_state(DFA::IntState* closure)
{
        vector<Transition*> epsilons = vector<Transition*>();
        for (int idx = 0; idx < transitions.size(); idx++) {
                if (transitions[idx]->get_epsilon()) {
                        epsilons.push_back(transitions[idx]);
                        continue;
                }

                closure->add_transition(transitions[idx]->get_dest(),
                                transitions[idx]->get_token());
        }

        closure->put_e_transition(this);

        if (this->get_end_state()) {
                closure->set_endstate();
        }

        for (int idx = 0; idx < epsilons.size(); idx++) {
                if (!closure->has_e_transition(epsilons[idx]->get_dest())) {
                        epsilons[idx]->get_dest()->build_closure_state(closure);
                }
        }

}

DFA::IntState* State::build_closure_state(bool is_epsilon)
{
        /* Make sure we don't run more than 1 time */
        if (closure != NULL) {
                return this->closure;
        }

        /* If we came in through an epsilon, cancel */
        if (is_epsilon) {

                closure = new DFA::IntState(
                                Alphabet::get_alphabet()->get_size());
                this->build_closure_state(closure);
        }

        /* Make all of our children do stuff */
        for (int idx = 0; idx < transitions.size(); idx++) {
                transitions[idx]->get_dest()->build_closure_state(
                                transitions[idx]->get_epsilon());
        }

        /* Couple all of our intermediate states into a fully functioning DFA */

        return closure;
}

void State::build_DFA_state()
{
        Alphabet* alpha = Alphabet::get_alphabet();
        this->int_state = new DFA::IntState(alpha->get_size());
}

State* State::get_DFA_state()
{
        return NULL;
}

} /* namespace NFA */
