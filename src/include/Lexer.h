/*
 * Parser.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <iostream>
#include <string>
#include <vector>

#include "Token.h"

namespace Lexer {

class Token;

class Lexer {
        Token* symbol_tree;
        size_t location;

        std::vector<Token*> symbolTypes;

public:
        Lexer(size_t location);
        virtual ~Lexer();
        Token* get_tokens();
        void set_tokens(Token* s);
        int build_grammar(std::string* rule);
        int enforceGrammar(std::string* line);

};

}

#endif /* SRC_PARSER_H_ */
