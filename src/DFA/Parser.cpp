
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
    std::vector<NFA::State*> empty = std::vector<NFA::State*>();
    this->dfa = new DFA::DFA_State(empty);


    // TODO: The actual conversion
    return this->dfa;
}

};
