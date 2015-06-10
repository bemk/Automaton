/*
 * Concat.h
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CONCAT_H_
#define SRC_CONCAT_H_

#include "Token.h"

namespace lexer {

class Concat: public Token {
private:
        bool concatenated;
        virtual void build_automata();
public:
        Concat(Lexer* p);
        virtual ~Concat();

        bool isOfType(char c);
        virtual Token* allocateType();
        virtual size_t build_grammar(std::string* rule, size_t location);
        virtual void do_concatenate();
};

}

#endif /* SRC_CONCAT_H_ */
