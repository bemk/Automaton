/*
 * Plus.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "../include/Plus.h"
#include <sstream>
using namespace std;


namespace lexer {

Plus::Plus(Parser* p) :
                Quantifier(p)
{
        this->start_at = START_ONE;
        this->stop_at = END_INFINITE;
        this->text = "+";
}

Plus::~Plus()
{
}

bool Plus::isOfType(char c)
{
        return (c == '+') ? true : false;
}

Symbol* Plus::allocateType()
{
        Symbol* s = new Plus(this->parser);

        if (s == NULL) {
                std::cerr << "Unable to allocate Plus descriptor" << std::endl;
                exit(-1);
        }
        return s;
}

void Plus::build_automata()
{
	if (this->automata.size()) {
		return;
	}

	init_automata();


	start->add_epsilon(in);
	out->add_epsilon(in);
	in->add_epsilon(this->getLeft()->get_start_symbol());
	this->getLeft()->get_start_symbol()->add_epsilon(out);
	out->add_epsilon(end);

	return;
}

}
