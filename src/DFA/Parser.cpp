/*
 * Parser.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/Parser.h"

using namespace std;

namespace DFA {

Parser::Parser(lexer::Token* tokens)
{
        this->tokens = tokens;
        this->states = vector<State*>();
}

Parser::~Parser()
{
        // TODO Auto-generated destructor stub
}

} /* namespace DFA */
