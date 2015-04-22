/*
 * Quantifier.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_QUANTIFIER_H_
#define SRC_QUANTIFIER_H_

#include "Automaton.h"

#define START_NULL 0
#define START_ONE  1

#define END_ONE 1
#define END_INFINITE -1

class Quantifier : Automaton{
private:
        int start_at;
        int stop_at;

public:
        Quantifier(std::string* rule);
        virtual ~Quantifier();
};

#endif /* SRC_QUANTIFIER_H_ */
