/*
 * Or.cpp
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#include "../include/Or.h"
#include <cstdlib>
#include <sstream>
using namespace std;

namespace lexer {

Or::Or(Lexer *p) : Token(p)
{
    // TODO Auto-generated constructor stub
    this->set_concatenation(false);
}

Or::~Or()
{
    // TODO Auto-generated destructor stub
}

size_t Or::build_grammar(string *s, size_t location)
{

    Token *prev = this->get_ll_prev();
    if (prev != NULL) {
        prev->set_ll_next(NULL);
    }
    this->set_ll_prev(NULL);

    this->location = location;
    if (s == NULL) {
        cerr << "Null string given at char " << location << "!" << endl;
        return 0;
    }
    if (s->compare("") == 0) {
        cerr << "Empty string given at char: " << location << "!" << endl;
        return 0;
    }

    this->text.push_back(s->at(0));
    Token *left = this->parser->get_tokens()->omit_starter();
    this->setLeft(left);
    left->setParent(this);

    Lexer *p = new Lexer(location + 1);

    string *sub = new string(s->substr(1));
    p->build_grammar(sub);
    delete sub;

    this->setRight(p->get_tokens()->omit_starter());
    this->getRight()->setParent(this);

    if (this->getRight()) {
        this->getRight()->set_parser(this->parser);
    }

    delete p;
    this->parser->set_tokens(this);

    return s->length();
}

void Or::do_concatenate()
{
    if (this->getLeft()) {
        this->getLeft()->do_concatenate();
    }
    if (this->getRight()) {
        this->getRight()->do_concatenate();
    }
}

bool Or::isOfType(char c)
{
    return (c == '|');
}

Token* Or::allocateType(void)
{
    Token *s = (Token*) new Or(this->parser);
    if (s == NULL) {
        cerr << "NULL POINTER ALLOCATED" << endl;
        exit(-1);
    }
    return s;
}

void Or::build_automata()
{
    if (this->automata.size()) {
        return;
    }

    stringstream name_start;
    stringstream name_top_in;
    stringstream name_top_out;
    stringstream name_bottom_in;
    stringstream name_bottom_out;
    stringstream name_end;

    stringstream tmp;

    name_start << "q_" << location << "_0";
    name_top_in << "q_" << location << "_1";
    name_top_out << "q_" << location << "_2";
    name_bottom_in << "q_" << location << "_3";
    name_bottom_out << "q_" << location << "_4";
    name_end << "q_" << location << "_5";

    NFA::State *start = new NFA::State(this->location, name_start.str());
    NFA::State *top_in = new NFA::State(this->location, name_top_in.str());
    NFA::State *top_out = new NFA::State(this->location, name_top_out.str());

    NFA::State *bottom_in = new NFA::State(
            this->location,
            name_bottom_in.str());
    NFA::State *bottom_out = new NFA::State(
            this->location,
            name_bottom_out.str());

    NFA::State *end = new NFA::State(this->location, name_end.str());

    this->start = start;
    this->end = end;

    start->add_epsilon(top_in);
    start->add_epsilon(bottom_in);

    top_in->add_epsilon(this->getLeft()->get_start_symbol());
    bottom_in->add_epsilon(this->getRight()->get_start_symbol());

    this->getLeft()->get_accept_symbol()->add_epsilon(top_out);
    this->getRight()->get_accept_symbol()->add_epsilon(bottom_out);

    top_out->add_epsilon(end);
    bottom_out->add_epsilon(end);

    this->automata.push_back(start);
    this->automata.push_back(top_in);
    this->automata.push_back(top_out);
    this->automata.push_back(bottom_in);
    this->automata.push_back(bottom_out);
    this->automata.push_back(end);

    return;
}

}
