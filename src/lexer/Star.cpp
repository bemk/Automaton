/*
 * Star.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas Moors & Bart Kuivenhoven
 */

#include "../include/Star.h"
#include <sstream>
using namespace std;

namespace Lexer {

Star::Star(Lexer *p) : Quantifier(p)
{
    this->start_at = START_NULL;
    this->stop_at = END_INFINITE;
    this->text = "*";
}

Star::~Star()
{
}

bool Star::isOfType(char c)
{
    return (c == '*');
}

Token* Star::allocateType()
{
    Token *s = new Star(this->parser);
    if (s == NULL) {
        std::cerr << "Unable to allocate new star descriptor" << std::endl;
        exit(-1);
    }
    return s;
}

void Star::build_automata()
{
    if (this->automata.size()) {
        return;
    }

    init_automata();

    start->add_epsilon(in);
    start->add_epsilon(out);
    out->add_epsilon(in);
    in->add_epsilon(this->getLeft()->get_start_symbol());
    this->getLeft()->get_accept_symbol()->add_epsilon(out);
    out->add_epsilon(end);

    return;
}

}
