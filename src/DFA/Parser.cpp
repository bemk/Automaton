/*
 * Parser.cpp
 *
 *  Created on: 9 Nov 2022
 *      Author: Bart Kuivenhoven
 */



#include "../include/DFA/Parser.h"
#include <sstream>
#include <iostream>
#include <set>

namespace DFA {

Parser::Parser(NFA::State* nfa)
{
    this->nfa = nfa;
}

Parser::~Parser()
{

}

void Parser::build_DFA(DFA_State* dfa)
{
    std::vector<NFA::State*> states_seen = std::vector<NFA::State*>();
    std::map<char, std::vector<NFA::State*>> transition_map = std::map<char, std::vector<NFA::State*>> ();
    for (NFA::State* s : dfa->get_sources()) {

        s->get_all_character_transitions(transition_map, states_seen);

        bool found_end_state = s->includes_end_state();
        if (found_end_state) {
            this->set_end_states.emplace(dfa);
            dfa->set_end_state(true);
        }
    }

    for (auto iterator : transition_map) {
        char token = iterator.first;
        std::vector<NFA::State*> targets = iterator.second;

        std::string name = generate_name(targets);
        DFA_State* dfa_target = dfa_states[name];


        if (dfa_target == NULL) {
            dfa_target = new DFA_State(targets, name);
            dfa_states[name] = dfa_target;
            build_DFA(dfa_target);
        }

        dfa->add_transition(token, dfa_target);
    }

}

NFA::State* Parser::build_DFA()
{
    std::vector<NFA::State*> initial = std::vector<NFA::State*>();
    initial.push_back(nfa);
    this->dfa = new DFA::DFA_State(initial, "q0");

    build_DFA(this->dfa);

    vector_end_states.clear();
    vector_end_states.insert(vector_end_states.end(), set_end_states.begin(), set_end_states.end());

    return this->dfa;
}

std::string Parser::generate_name(std::vector<NFA::State*> sources)
{
    std::set<NFA::State*> source_set;
    source_set.insert(sources.begin(), sources.end());

    std::stringstream builder = std::stringstream();
    for (auto i : source_set) {
        std::string name = *i->get_name();
        builder << name;
    }

    return builder.str();
}

};
