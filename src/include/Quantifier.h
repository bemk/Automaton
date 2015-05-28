/*
 * Quantifier.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_QUANTIFIER_H_
#define SRC_QUANTIFIER_H_

#include "Symbol.h"
#include <cstdlib>

#define START_NULL 0
#define START_ONE  1

#define END_ONE 1
#define END_INFINITE -1

namespace lexer {

class Quantifier : public Symbol {
protected:
        int start_at;
        int stop_at;

public:
        Quantifier(Parser* p);
        virtual ~Quantifier();

        virtual size_t build_grammar(std::string* rule, size_t location);
        virtual bool isOfType(char);
        virtual Symbol* allocateType();
};

}

#endif /* SRC_QUANTIFIER_H_ */
