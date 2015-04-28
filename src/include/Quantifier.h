/*
 * Quantifier.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_QUANTIFIER_H_
#define SRC_QUANTIFIER_H_

#include "Symbol.h"

#define START_NULL 0
#define START_ONE  1

#define END_ONE 1
#define END_INFINITE -1

class Quantifier : public Symbol {
private:
        int start_at;
        int stop_at;

public:
        Quantifier();
        virtual ~Quantifier();

        virtual size_t build_grammar(std::string* rule);
        virtual bool isOfType(char);
        virtual Symbol* allocateType();
};

#endif /* SRC_QUANTIFIER_H_ */
