/*
 * Parser.h
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_DFA_PARSER_H_
#define SRC_INCLUDE_DFA_PARSER_H_

#include "../Token.h"
#include <vector>

namespace DFA {

class Parser {
private:
        lexer::Token* tokens;
        std::vector<State*> states;

public:
        Parser(lexer::Token* tokens);
        virtual ~Parser();

};

} /* namespace DFA */

#endif /* SRC_INCLUDE_DFA_PARSER_H_ */
