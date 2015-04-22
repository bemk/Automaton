/*
 * Quantifier.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_QUANTIFIER_H_
#define SRC_QUANTIFIER_H_

#include "Automaton.h"

class Quantifier : Automaton{
public:
        Quantifier(std::string* rule);
        virtual ~Quantifier();
};

#endif /* SRC_QUANTIFIER_H_ */
