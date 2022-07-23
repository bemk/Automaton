/*
 * Symbol.cpp
 *
 *  Created on: 23 Apr 2015
 *      Author: bemk
 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "../include/Alphabet.h"
#include "../include/Token.h"

using namespace std;

extern bool verbose;

namespace lexer {

Token::Token(Lexer *p)
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
    this->start = NULL;
    this->end = NULL;

    this->automata = vector<NFA::State*>();
}

Token::~Token()
{
}

size_t Token::build_grammar(string *s, size_t location)
{
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

    Alphabet *alphabet = Alphabet::get_alphabet();
    alphabet->push_char(s->at(0));

    return 1;
}

string* Token::getString()
{
    return &this->text;
}

Token* Token::getLeft()
{
    return left;
}

Token* Token::getRight()
{
    return right;
}

Token* Token::getParent()
{
    return top;
}

void Token::setRight(Token *symbol)
{
    this->right = symbol;
}

void Token::setLeft(Token *symbol)
{
    this->left = symbol;
}

void Token::setParent(Token *parent)
{
    this->top = parent;
}

void Token::set_parser(Lexer *p)
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

void build_name(string *name, Token *ptr)
{
    if (name->length() > 1) {
        name->assign("cap");
    } else if (name->compare("|") == 0) {
        name->assign("or");
    } else if (name->length() == 0) {
        stringstream tmp;
        tmp << "starter_" << ptr;
        name->assign(tmp.str());
    } else if (name->compare("*") == 0) {
        name->assign("star");
    } else if (name->compare("+") == 0) {
        name->assign("plus");
    } else if (name->compare("?") == 0) {
        name->assign("questionmark");
    } else if (name->compare(".") == 0) {
        name->assign("dot");
    }

    if (ptr->concatenation_allowed()) {
        name->append("_APPEND");
    }
}

void Token::do_concatenate()
{
    if (this->get_ll_next()) {
        this->get_ll_next()->do_concatenate();
    }
    return;
}

bool Token::get_dot_reference(string *ret, string src_name, string ref_name)
{
    string tmp = "";

    string tmp_text = text;
    build_name(&tmp_text, this);

    stringstream name_stream;
    name_stream << "symbol_" << location << "_" << tmp_text;
    string name = name_stream.str();

    tmp.append(src_name);
    tmp.append(" -> ");
    tmp.append(name);
    tmp.append(" [label=\"");
    tmp.append(ref_name);
    tmp.append("\"];\n");

    ret->append(tmp);

    return true;
}

bool Token::get_dot_graph(string *s)
{
    if (s == NULL) {
        return false;
    }

    string tmp_text = text;

    build_name(&tmp_text, this);

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

    if (this->getParent()) {
        this->getParent()->get_dot_reference(s, name, "parent");
    }

    return true;
}

bool Token::isOfType(char c)
{
    return true;
}

Token* Token::allocateType()
{
    Token *s = new Token(this->parser);
    if (s == NULL) {
        std::cerr << "NULL POINTER ALLOCATED" << endl;
        exit(-1);
    }
    return s;
}

void Token::set_ll_next(Token *s)
{
    this->ll_next = s;
}

void Token::set_ll_prev(Token *s)
{
    this->ll_prev = s;
}

Token* Token::get_ll_next()
{
    return this->ll_next;
}

Token* Token::get_ll_prev()
{
    return this->ll_prev;
}

Token* Token::get_ll_last()
{
    if (this->ll_next == NULL) {
        return this;
    }
    return this->ll_next->get_ll_last();
}

bool Token::concatenation_allowed()
{
    return this->allow_concatenation;
}

void Token::set_concatenation(bool status)
{
    this->allow_concatenation = status;
}

void Token::set_location(size_t location)
{
    this->location = location;
}

Token* Token::omit_starter()
{
    return this;
}

void Token::build_automata()
{
    if (this->automata.size()) {
        return;
    }

    stringstream start_stream;
    stringstream end_stream;

    start_stream << "qs_" << this->location << "_0";
    end_stream << "qs_" << this->location << "_1";

    NFA::State *start = new NFA::State(this->location, start_stream.str());
    NFA::State *end = new NFA::State(this->location, end_stream.str());

    this->start = start;
    this->end = end;

    start->add_transition(this->text[0], end);

    this->automata.push_back(start);
    this->automata.push_back(end);

    return;
}

NFA::State* Token::get_start_symbol()
{
    build_automata();
    return this->start;
}

NFA::State* Token::get_accept_symbol()
{
    build_automata();
    return this->end;
}

}
