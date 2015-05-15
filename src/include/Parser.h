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
#include "Symbol.h"

class Parser {
        Symbol* symbol_tree;
        size_t location;

        std::vector<Symbol*> symbolTypes;

public:
        Parser(size_t location);
        virtual ~Parser();
        Symbol* getSymbols();
        int build_grammar(std::string* rule);
        int enforceGrammar(std::string* line);
};

#endif /* SRC_PARSER_H_ */
