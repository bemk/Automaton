
#include "../include/DFA/Parser.h"
#include <sstream>

namespace DFA {

Parser::Parser(NFA::State* nfa)
{
    this->nfa = nfa;
}

Parser::~Parser()
{

}

NFA::State* Parser::build_DFA()
{
    std::vector<NFA::State*> initial = std::vector<NFA::State*>();
    initial.push_back(nfa);
    this->dfa = new DFA::DFA_State(initial, "q_0");


    std::map<char, std::vector<NFA::State*>> transition_map = nfa->get_all_character_transitions();
    for (auto iterator : transition_map) {
        char token = iterator.first;
        std::vector<NFA::State*> targets = iterator.second;

        std::string name = generate_name(targets);
        DFA_State* dfa_target = dfa_states[name];

        if (dfa_target == NULL) {
            dfa_target = new DFA_State(targets, name);
            dfa_states[name] = dfa_target;
        }

        dfa->add_transition(token, dfa_target);
    }
    return this->dfa;
}

std::string Parser::generate_name(std::vector<NFA::State*> sources)
{
    std::stringstream builder = std::stringstream();
    for (int i = 0; i < sources.size(); i++) {
        builder << sources[i]->get_name();
        if (i < (sources.size() - 1)) {
            builder << ",";
        }
    }

    return builder.str();
}

};
