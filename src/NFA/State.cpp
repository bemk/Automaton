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
#include "../include/Alphabet.h"

using namespace std;
extern bool simple_graph;
extern bool reset_id_alloc;

namespace NFA {

static int unique_id_alloc = 0;

State::State(size_t location, string name)
{
        this->end_state = false;

        if (reset_id_alloc) {
            reset_id_alloc = false;
            unique_id_alloc = 0;
        }

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
        this->parsed = false;
        this->location = location;
        this->transitions = vector<Transition*>();
        this->incoming = vector<Transition*>();

        this->closure = NULL;
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

        Transition* transition = new Transition(
                this->location,
                name,
                this,
                dest);

        this->transitions.push_back(transition);
        dest->add_incoming(transition);

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
        dest->add_incoming(t);

        return;
}

bool State::get_dot_graph(string* s)
{
        if (s == NULL || graphed) {
                return false;
        }

        graphed = true;

        bool to_graph = true;
        if (incoming.size() == 1 && transitions.size() == 1) {
                if (incoming[0]->get_epsilon() && transitions[0]->get_epsilon()) {
                        to_graph = false;
                }
        }

        for (size_t i = 0; i < transitions.size(); i++) {
                if (to_graph) {
                        transitions[i]
                                    ->get_dest()
                                    ->get_dot_reference(
                                            s,
                                            &name,
                                            this->transitions[i]->get_epsilon(),
                                            this->transitions[i]->get_token());
                }
                transitions[i]->get_dest()->get_dot_graph(s);
        }

        return true;
}

void State::get_dot_reference(
    std::string* s,
    std::string* caller,
    bool epsylon,
    char input)
{
        if (this->incoming.size() == 1 && this->transitions.size() == 1) {
                if (incoming[0]->get_epsilon() && transitions[0]->get_epsilon()) {
                        transitions[0]
                                    ->get_dest()
                                    ->get_dot_reference(
                                s,
                                caller,
                                true,
                                input);
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

bool State::includes_end_state(std::vector<NFA::State*>& seen)
{
    for (State* s : seen) {
        if (s == this) {
            return false;
        }
    }

    if (this->end_state) {
        return true;
    }

    seen.push_back(this);

    for (auto t : transitions) {
        if (t->get_epsilon()) {
            if (t->get_dest()->includes_end_state(seen)) {
                return true;
            }
        }
    }

    return false;
}

bool State::includes_end_state()
{
    std::vector<NFA::State*> seen = std::vector<NFA::State*>();
    return includes_end_state(seen);
}

std::vector<State*>* State::get_states_for(char c, std::vector<State*>* seen)
{
    for (int i = 0; i < seen->size(); i++) {
        if (seen->at(i) == this) {
            return seen;
        }
    }

    seen->push_back(this);
    for (auto t : transitions) {
       if (t->get_token() == c)  {
           seen->push_back(t->get_dest());
       } else if (t->get_epsilon()) {
           t->get_dest()->get_states_for(c, seen);
       }
    }
    return seen;
}

std::vector<State*>* State::get_states_for(char c)
{
    std::vector<NFA::State*>* seen = new std::vector<State*>();

    return get_states_for(c, seen);
}


void State::get_all_character_transitions(std::map<char, std::vector<State*>>& transition_map, std::vector<NFA::State*>& seen)
{
    for (State* s : seen) {
        if (s == this) {
            return;
        }
    }
    seen.push_back(this);

    for (Transition* t : this->transitions) {
        if (t->get_epsilon()) {
            State* s = t->get_dest();
            s->get_all_character_transitions(transition_map, seen);
        } else {
            transition_map[t->get_token()].push_back(t->get_dest());
        }
    }
}

std::map<char, std::vector<State*>>& State::get_all_character_transitions() {
    std::vector<NFA::State*> seen = std::vector<NFA::State*>();
    get_all_character_transitions(transition_map, seen);

    return this->transition_map;
}

} /* namespace NFA */
