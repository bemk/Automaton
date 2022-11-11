/*
 * Parser.h
 *
 *  Created on: 9 Nov 2022
 *      Author: bemk
 */

#include <map>
#include "../NFA/State.h"
#include "DFAState.h"

#ifndef SRC_INCLUDE_DFA_PARSER_H_
#define SRC_INCLUDE_DFA_PARSER_H_

namespace DFA {

    class Parser {
    private:
        NFA::State* nfa = NULL;
        NFA::State* dfa = NULL;

        std::map<std::string, DFA_State*> dfa_states = std::map<std::string, DFA_State*>();

        std::string generate_name(std::vector<NFA::State*> sources);
    public:
        Parser(NFA::State* nfa);
        ~Parser();

        NFA::State* build_DFA();

    };

};


#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
