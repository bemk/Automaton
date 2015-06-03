/*
 * Or.cpp
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#include "../include/Or.h"
#include <cstdlib>
using namespace std;

namespace lexer {

Or::Or(Parser* p) :
                Symbol(p)
{
        // TODO Auto-generated constructor stub
        this->set_concatenation(false);
}

Or::~Or()
{
        // TODO Auto-generated destructor stub
}

size_t Or::build_grammar(string* s, size_t location)
{

        Symbol* prev = this->get_ll_prev();
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
                cerr << "Empty string given at char: " << location << "!"
                << endl;
                return 0;
        }

        this->text.push_back(s->at(0));

        Symbol* left = this->parser->get_symbols()->omit_starter();
        this->setLeft(left);
        left->setParent(this);

        Parser* p = new Parser(location + 1);

        string* sub = new string(s->substr(1));
        p->build_grammar(sub);
        delete sub;

        this->setRight(p->get_symbols()->omit_starter());
        this->getRight()->setParent(this);

        if (this->getRight()) {
                this->getRight()->set_parser(this->parser);
        }

        delete p;
        this->parser->set_symbols(this);

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
        if (c == '|') {
                return true;
        }
        return false;
}

Symbol* Or::allocateType(void)
{
        Symbol* s = (Symbol*) new Or(this->parser);
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

        string name_start = "";
        string name_top_in = "";
        string name_top_out = "";
        string name_bottom_in = "";
        string name_bottom_out = "";
        string name_end = "";

        name_start = location + "0";
        name_top_in = location + "1";
        name_top_out = location + "2";
        name_bottom_in = location + "3";
        name_bottom_out = location + "4";
        name_end = location + "5";

        NFA::Automaton* start = new NFA::Automaton(this->location, name_start);
        NFA::Automaton* top_in = new NFA::Automaton(this->location,
                        name_top_in);
        NFA::Automaton* top_out = new NFA::Automaton(this->location,
                        name_top_out);

        NFA::Automaton* bottom_in = new NFA::Automaton(this->location,
                        name_bottom_in);
        NFA::Automaton* bottom_out = new NFA::Automaton(this->location,
                        name_bottom_out);

        NFA::Automaton* end = new NFA::Automaton(this->location, name_end);

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
