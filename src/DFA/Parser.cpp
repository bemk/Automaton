
#include "../include/DFA/Parser.h"

namespace DFA {

Parser::Parser(NFA::State* nfa)
{
    this->nfa = nfa;
}

Parser::~Parser()
{

}

NFA::State* Parser::build_DFA()
{
    // TODO: The actual conversion
    return this->dfa;
}

};
