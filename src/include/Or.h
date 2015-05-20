/*
 * Or.h
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#ifndef AUTOMATON_SRC_OR_H_
#define AUTOMATON_SRC_OR_H_

#include "Symbol.h"

class Or: public Symbol {
public:
        Or(Parser* p);
        virtual ~Or();
        size_t build_grammar(std::string* s, size_t location);
        bool isOfType(char c);
        Symbol* allocateType(void);
};

#endif /* AUTOMATON_SRC_OR_H_ */
