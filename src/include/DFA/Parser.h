/*
 * Parser.h
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_DFA_PARSER_H_
#define SRC_INCLUDE_DFA_PARSER_H_

#include "../Token.h"
#include "State.h"
#include <vector>

namespace DFA {

class Parser {
private:
        lexer::Token* tokens;
        std::vector<State*> states;

        State* DFA;

public:
        Parser(lexer::Token* tokens);
        virtual ~Parser();

        void parse();

        State* get_dfa();

};

} /* namespace DFA */

#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
