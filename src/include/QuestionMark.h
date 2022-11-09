/*
 * QuestionMark.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_QUESTIONMARK_H_
#define AUTOMATON_SRC_QUESTIONMARK_H_

#include "Quantifier.h"

namespace Lexer {

class QuestionMark: public Quantifier {
public:
        QuestionMark(Lexer* p);
        virtual ~QuestionMark();
        virtual bool isOfType(char c);
        virtual Token* allocateType();

protected:
	virtual void build_automata();
};

}

#endif /* AUTOMATON_SRC_QUESTIONMARK_H_ */
