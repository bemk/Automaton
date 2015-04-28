/*
 * Symbol.cpp
 *
 *  Created on: 23 Apr 2015
 *      Author: bemk
 */

#include "include/Symbol.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Symbol::Symbol()
{
        left = NULL;
        right = NULL;

        ll_prev = NULL;
        ll_next = NULL;

        string_litteral = STRING_LITTERAL;
        text = string("");
}

Symbol::~Symbol()
{
}

size_t Symbol::build_grammar(string* s)
{
        if (s == NULL) {
                return -2;
        }
        if (s->compare("")) {
                return -1;
        }
        return 1;
}

string* Symbol::getString()
{
        return &this->text;
}

Symbol* Symbol::getLeft()
{
        return left;
}

Symbol* Symbol::getRight()
{
        return right;
}

void Symbol::setRight(Symbol* symbol)
{
        this->right = symbol;
}

void Symbol::setLeft(Symbol* symbol)
{
        this->left = symbol;
}

bool Symbol::isOfType(char c)
{
        return true;
}

Symbol* Symbol::allocateType()
{
        Symbol* s = new Symbol();
        if (s == NULL) {
                std::cerr << "NULL POINTER ALLOCATED" << endl;
                exit(-1);
        }
        return s;
}

void Symbol::set_ll_next(Symbol* s)
{
        this->ll_next = s;
}

void Symbol::set_ll_prev(Symbol* s)
{
        this->ll_prev = s;
}

Symbol* Symbol::get_ll_next()
{
        return this->ll_next;
}

Symbol* Symbol::get_ll_prev()
{
        return this->ll_prev;
}
