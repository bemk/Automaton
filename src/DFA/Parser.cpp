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

        tokens->get_accept_symbol()->set_end_state(true);

        this->states = vector<State*>();
        this->DFA = NULL;
}

Parser::~Parser()
{
        // TODO Auto-generated destructor stub
}

void Parser::parse()
{
        vector<State*> to_parse = vector<State*>();
        IntState* tmp = this->tokens->get_start_symbol()->build_closure_state(
                        false);
        this->DFA = tmp->build_dfa_state();
}

State* Parser::get_dfa()
{
        return this->DFA;
}

} /* namespace DFA */
