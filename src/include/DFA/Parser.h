/*
 * Parser.h
 *
 *  Created on: 9 Nov 2022
 *      Author: bemk
 */

#include "../NFA/State.h"

#ifndef SRC_INCLUDE_DFA_PARSER_H_
#define SRC_INCLUDE_DFA_PARSER_H_

namespace DFA {

    class Parser {
    private:
        NFA::State* nfa = NULL;
        NFA::State* dfa = NULL;
    public:
        Parser(NFA::State* nfa) {this->nfa = nfa;};
        ~Parser();

        NFA::State* buildDFA(NFA::State* state);

    };

};


#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
