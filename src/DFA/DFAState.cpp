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

} /* namespace DFA */
