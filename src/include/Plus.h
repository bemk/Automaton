/*
 * Plus.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_PLUS_H_
#define AUTOMATON_PLUS_H_

#include "Quantifier.h"

namespace lexer {

class Plus: public Quantifier {
public:
        Plus(Lexer* p);
        virtual ~Plus();
        virtual bool isOfType(char c);
        virtual Token* allocateType();
protected:
	virtual void build_automata();
};

}

#endif /* AUTOMATON_PLUS_H_ */
