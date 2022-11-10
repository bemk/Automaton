/*
 * DFAState.cpp
 *
 *  Created on: 10 Nov 2022
 *      Author: bemk
 */

#include "../include/DFA/DFAState.h"
#include <sstream>

namespace DFA {

DFA_State::DFA_State(std::vector<NFA::State*>& sources) : NFA::State(0, "null")
{
    this->add_sources(sources);
    this->generate_name();
}

DFA_State::~DFA_State()
{
}

void DFA_State::generate_name()
{
    std::stringstream builder = std::stringstream();
    for (int i = 0; i < sources.size(); i++) {
        builder << sources[i]->get_name();
        if (i < (sources.size() - 1)) {
            builder << ",";
        }
    }

    this->name = builder.str();

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
