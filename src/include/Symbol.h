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

#define STRING_LITTERAL -1
#define STRING_OPERATOR 0

class Symbol {
        Symbol* left;
        Symbol* right;

        Symbol* ll_next;
        Symbol* ll_prev;

        int string_litteral;

protected:
        size_t location;
        std::string text;

public:
        Symbol();
        virtual ~Symbol();

        virtual size_t build_grammar(std::string* s, size_t location);
        std::string* getString();

        Symbol* getLeft();
        Symbol* getRight();

        Symbol* get_ll_next();
        Symbol* get_ll_prev();

        void setLeft(Symbol*);
        void setRight(Symbol*);

        void set_ll_next(Symbol* s);
        void set_ll_prev(Symbol* s);

        virtual bool isOfType(char c);
        virtual bool allow_concatenation();
        virtual Symbol* allocateType();
};

#endif /* SRC_SYMBOL_H_ */
