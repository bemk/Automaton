/*
 * Symbol.cpp
 *
 *  Created on: 23 Apr 2015
 *      Author: bemk
 */

#include "include/Symbol.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "include/Alphabet.h"

using namespace std;

extern bool verbose;

Symbol::Symbol(Parser* p)
{
        location = 0;
        left = NULL;
        right = NULL;
        top = NULL;

        ll_prev = NULL;
        ll_next = NULL;

        string_litteral = STRING_LITTERAL;
        text = string("");

        allow_concatenation = true;
        this->parser = p;
}

Symbol::~Symbol()
{
}

size_t Symbol::build_grammar(string* s, size_t location)
{
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

        Alphabet* alphabet = Alphabet::get_alphabet();
        alphabet->push_char(s->at(0));

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

Symbol* Symbol::getParent()
{
        return top;
}

void Symbol::setRight(Symbol* symbol)
{
        this->right = symbol;
}

void Symbol::setLeft(Symbol* symbol)
{
        this->left = symbol;
}

void Symbol::setParent(Symbol* parent)
{
        this->top = parent;
}

void Symbol::set_parser(Parser* p)
{
        if (this->parser == p) {
                if (verbose) {
                        cout << "Parser already set in " << this->text << endl;
                }
                return;
        }

        this->parser = p;

        if (this->left) {
                left->set_parser(p);
        }
        if (this->right) {
                right->set_parser(p);
        }
        if (this->ll_next) {
                ll_next->set_parser(p);
        }
        /*
         * Note:
         *
         * Don't set the previous pointer, because it will generate an infinite
         * loop. Also, it should already be set by the caller to begin with.
         */

}

bool Symbol::get_dot_reference(string* ret, string src_name, string ref_name)
{
        string tmp = "";

        string tmp_text = text;
        if (tmp_text.length() > 1) {
                tmp_text = "cap";
        }
        if (tmp_text.compare("|") == 0) {
                tmp_text = "or";
        }

        stringstream name_stream;
        name_stream << "symbol_" << location << "_" << tmp_text;
        string name = name_stream.str();

        /*
        if (name.compare("symbol_0_") == 0 || src_name.compare("symbol_0_") == 0) {
                return true;
        }
        */
        tmp.append(src_name);
        tmp.append(" -> ");
        tmp.append(name);
        tmp.append(" [label=\"");
        tmp.append(ref_name);
        tmp.append("\"];\n");

        ret->append(tmp);

        return true;
}

bool Symbol::get_dot_graph(string* s)
{
        if (s == NULL) {
                return false;
        }

        string tmp_text = text;
        if (tmp_text.length() > 1) {
                tmp_text = "cap";
        }
        if (tmp_text.compare("|") == 0) {
                tmp_text = "or";
        }
        stringstream name_stream;
        name_stream << "symbol_" << location << "_" << tmp_text;
        string name = name_stream.str();

        if (this->get_ll_prev()) {
                this->get_ll_prev()->get_dot_reference(s, name, "prev");
        }

        if (this->get_ll_next()) {
                this->get_ll_next()->get_dot_reference(s, name, "next");
                this->get_ll_next()->get_dot_graph(s);
        }

        if (this->getLeft()) {
                this->getLeft()->get_dot_reference(s, name, "left");
                this->getLeft()->get_dot_graph(s);
        }

        if (this->getRight()) {
                this->getRight()->get_dot_reference(s, name, "right");
                this->getRight()->get_dot_graph(s);
        }

        return true;
}

bool Symbol::isOfType(char c)
{
        return true;
}

Symbol* Symbol::allocateType()
{
        Symbol* s = new Symbol(this->parser);
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

Symbol* Symbol::get_ll_last()
{
        if (this->ll_next == NULL) {
                return this;
        }
        return this->ll_next->get_ll_last();
}

bool Symbol::concatenation_allowed()
{
        return this->allow_concatenation;
}

void Symbol::set_concatenation(bool status)
{
        this->allow_concatenation = status;
}

