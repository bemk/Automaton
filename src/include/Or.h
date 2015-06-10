/*
 * Or.h
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_OR_H_
#define AUTOMATON_SRC_OR_H_

#include "Token.h"

namespace lexer {

class Or: public Token {
protected:
        virtual void build_automata();
public:
        Or(Lexer* p);
        virtual ~Or();
        size_t build_grammar(std::string* s, size_t location);
        bool isOfType(char c);
        Token* allocateType(void);
        virtual void do_concatenate();
};

}

#endif /* AUTOMATON_SRC_OR_H_ */
