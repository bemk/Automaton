/*
 * Star.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_STAR_H_
#define AUTOMATON_SRC_STAR_H_

#include "Quantifier.h"

namespace Lexer {

class Star: public Quantifier {
public:
        Star(Lexer* p);
        virtual ~Star();
        virtual bool isOfType(char c);
        virtual Token* allocateType();

protected:
	virtual void build_automata();
};

}

#endif /* AUTOMATON_SRC_STAR_H_ */
