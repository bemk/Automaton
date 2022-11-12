/*
 * Quantifier.h
 *
 *  Created on: 22 Apr 2015
 *      Author: Thomas Moors & Bart Kuivenhoven
 */

#ifndef SRC_QUANTIFIER_H_
#define SRC_QUANTIFIER_H_

#include <cstdlib>
#include <iostream>
#include "Token.h"

#define START_NULL 0
#define START_ONE  1

#define END_ONE 1
#define END_INFINITE -1

namespace Lexer {

class Quantifier : public Token {
protected:
        int start_at;
        int stop_at;

		
		NFA::State* in;
		NFA::State* out;

		void init_automata();
		void build_automata() {
			std::cerr << "Something went horribly wrong at char " << this->location << std::endl;
			exit(-404);
		}

public:
        Quantifier(Lexer* p);
        virtual ~Quantifier();

        virtual size_t build_grammar(std::string* rule, size_t location);
        virtual bool isOfType(char);
        virtual Token* allocateType();
};

}

#endif /* SRC_QUANTIFIER_H_ */
