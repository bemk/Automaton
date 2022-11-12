/*
 * Parser.h
 *
 *  Created on: 9 Nov 2022
 *      Author: Bart Kuivenhoven
 */

#include <map>
#include <unordered_set>

#include "../NFA/State.h"
#include "DFAState.h"

#ifndef SRC_INCLUDE_DFA_PARSER_H_
#define SRC_INCLUDE_DFA_PARSER_H_

namespace DFA {

    class Parser {
    private:
        NFA::State* nfa = NULL;
        DFA_State* dfa = NULL;

        std::map<std::string, DFA_State*> dfa_states = std::map<std::string, DFA_State*>();
        std::unordered_set<NFA::State*> set_end_states = std::unordered_set<NFA::State*>();
        std::vector<NFA::State*> vector_end_states = std::vector<NFA::State*>();

        std::string generate_name(std::vector<NFA::State*> sources);
        void build_DFA(DFA_State* dfa);
    public:
        Parser(NFA::State* nfa);
        ~Parser();

        NFA::State* build_DFA();

        std::vector<NFA::State*> get_end_states() {return vector_end_states;}

    };

};


#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
