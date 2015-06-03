/*
 * Quantifier.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "../include/Quantifier.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

namespace lexer {

Quantifier::Quantifier(Parser* p) :
                Symbol(p)
{
        /* If no quantifier is given, default to exactly one */
        start_at = START_ONE;
        stop_at = END_ONE;

        this->in = NULL;
        this->out = NULL;
}

size_t Quantifier::build_grammar(string* rule, size_t location)
{
        this->location = location;

        Symbol* prev = this->get_ll_prev();
        Symbol* dPrev = prev->get_ll_prev();

        dPrev->set_ll_next(this);
        this->set_ll_prev(dPrev);

        prev->set_ll_prev(NULL);
        prev->set_ll_next(NULL);

        this->setLeft(prev);
        prev->setParent(this);

        return 1;
}

Quantifier::~Quantifier()
{
}

bool Quantifier::isOfType(char c)
{
        return false;
}

Symbol* Quantifier::allocateType()
{
        cerr << "Generic quantifier should never be found!!!" << endl;
        return NULL;
}

void Quantifier::init_automata()
{
        stringstream name_start;
        stringstream name_in;
        stringstream name_out;
        stringstream name_end;

        name_start << "qq_" << this->location << "_0";
        name_in << "qq_" << this->location << "_1";
        name_out << "qq_" << this->location << "_2";
        name_end << "qq_" << this->location << "_3";

        NFA::Automaton* start = new NFA::Automaton(this->location,
                        name_start.str());
        NFA::Automaton* in = new NFA::Automaton(this->location, name_in.str());
        NFA::Automaton* out = new NFA::Automaton(this->location,
                        name_out.str());
        NFA::Automaton* end = new NFA::Automaton(this->location,
                        name_end.str());

        this->start = start;
        this->in = in;
        this->out = out;
        this->end = end;

        this->automata.push_back(start);
        this->automata.push_back(in);
        this->automata.push_back(out);
        this->automata.push_back(end);
}

}
