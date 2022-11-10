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

        std::map<std::string, NFA::State*> dfa_states = std::map<std::string, NFA::State*>();

    public:
        Parser(NFA::State* nfa);
        ~Parser();

        NFA::State* build_DFA();

    };

};


#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
