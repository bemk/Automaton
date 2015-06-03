/*
 * QuestionMark.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_QUESTIONMARK_H_
#define AUTOMATON_SRC_QUESTIONMARK_H_

#include "Quantifier.h"

namespace lexer {

class QuestionMark: public Quantifier {
public:
        QuestionMark(Parser* p);
        virtual ~QuestionMark();
        virtual bool isOfType(char c);
        virtual Symbol* allocateType();

protected:
	virtual void build_automata();
};

}

#endif /* AUTOMATON_SRC_QUESTIONMARK_H_ */
