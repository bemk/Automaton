/*
 * Or.cpp
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#include "include/Or.h"
#include <cstdlib>
using namespace std;

Or::Or(Parser* p) :
                Symbol(p)
{
        // TODO Auto-generated constructor stub

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

        Symbol* left = this->parser->get_symbols()->ommit_starter();
        this->setLeft(left);

        Parser* p = new Parser(location + 1);

        string* sub = new string(s->substr(1));
        p->build_grammar(sub);
        delete sub;

        this->setRight(p->get_symbols()->ommit_starter());
        this->getRight()->setParent(this);

        if (this->getRight()) {
                this->getRight()->set_parser(this->parser);
        }

        delete p;
        this->parser->set_symbols(this);

        return s->length();
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

