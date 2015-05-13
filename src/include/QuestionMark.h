/*
 * QuestionMark.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_QUESTIONMARK_H_
#define AUTOMATON_SRC_QUESTIONMARK_H_

#include "Quantifier.h"

class QuestionMark: public Quantifier {
public:
        QuestionMark();
        virtual ~QuestionMark();
        virtual bool isOfType(char c);
};

#endif /* AUTOMATON_SRC_QUESTIONMARK_H_ */
