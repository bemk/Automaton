/*
 * DFAState.cpp
 *
 *  Created on: 10 Nov 2022
 *      Author: bemk
 */

#include "../include/DFA/DFAState.h"
#include <sstream>

namespace DFA {

DFA_State::DFA_State(std::vector<NFA::State*>& sources, std::string name) : NFA::State(0, name)
{
    this->add_sources(sources);
}

DFA_State::~DFA_State()
{
}

void DFA_State::add_source(NFA::State* state)
{
    for (size_t i = 0; i < sources.size(); i++) {
        if (sources[i] == state) {
            return;
        }
    }

    sources.push_back(state);
}

void DFA_State::add_sources(std::vector<NFA::State*>& sources)
{
    for (auto s : sources) {
        add_source(s);
    }
}

bool DFA_State::enforce(const char* input)
{
    char head = input[0];
    if (head == '\0' && this->end_state) {
        return true;
    } else if (head == '\0') {
        return false;
    }

    NFA::Transition* found = NULL;
    for (NFA::Transition* i : transitions) {
        if (i->get_token() == head) {
            found = i;
        }
    }
    if (found == NULL) {
        return false;
    }

    DFA_State* target = (DFA_State*)found->get_dest();
    return target->enforce(&input[1]);
}

void DFA_State::build_word(std::string path, size_t depth)
{
    if (end_state) {
        std::cout << path << std::endl;
    }

    if (depth == 0) {
        return;
    }

    for (auto t: transitions) {
        ((DFA_State*)t->get_dest())->build_word(path + t->get_token(), depth-1);
    }
}

void DFA_State::build_word(size_t depth)
{
    build_word("", depth);
}

} /* namespace DFA */
