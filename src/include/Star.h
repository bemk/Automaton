/*
 * Star.h
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_STAR_H_
#define AUTOMATON_SRC_STAR_H_

#include "Quantifier.h"

class Star: public Quantifier {
public:
        Star();
        virtual ~Star();
        virtual bool isOfType(char c);
};

#endif /* AUTOMATON_SRC_STAR_H_ */
