/*
 * Plus.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_PLUS_H_
#define AUTOMATON_PLUS_H_

#include "Quantifier.h"

class Plus: public Quantifier {
public:
        Plus();
        virtual ~Plus();
        virtual bool isOfType(char c);
};

#endif /* AUTOMATON_PLUS_H_ */