/*
 * Symbol.h
 *
 *  Created on: 23 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_SYMBOL_H_
#define SRC_SYMBOL_H_

#include <string>
#include <iostream>
#include "Lexer.h"
#include "NFA/State.h"

#define STRING_LITTERAL -1
#define STRING_OPERATOR 0

namespace lexer {

class Lexer;

class Token {
    Token *left;
    Token *right;
    Token *top;

    Token *ll_next;
    Token *ll_prev;

    bool allow_concatenation;

    int string_litteral;

protected:
    size_t location;
    std::string text;
    Lexer *parser;

    bool get_dot_reference(std::string *ret,
        std::string src_name,
        std::string ref_name);

    std::vector<NFA::State*> automata;
    NFA::State *start;
    NFA::State *end;

    virtual void build_automata();

public:
    Token(Lexer *p);
    virtual ~Token();

    virtual size_t build_grammar(std::string *s, size_t location);
    std::string* getString();

    Token* getLeft();
    Token* getRight();
    Token* getParent();

    Token* get_ll_next();
    Token* get_ll_prev();
    Token* get_ll_last();
    virtual void do_concatenate();

    void setLeft(Token*);
    void setRight(Token*);
    void setParent(Token*);

    void set_parser(Lexer *p);
    bool get_dot_graph(std::string *s);

    void set_ll_next(Token *s);
    void set_ll_prev(Token *s);

    virtual bool isOfType(char c);
    virtual bool concatenation_allowed();
    virtual void set_concatenation(bool status);
    virtual Token* allocateType();

    virtual Token* omit_starter();

    void set_location(size_t location);
    size_t get_location()
    {
        return this->location;
    }

    NFA::State* get_start_symbol();
    NFA::State* get_accept_symbol();
};

}

#endif /* SRC_SYMBOL_H_ */
