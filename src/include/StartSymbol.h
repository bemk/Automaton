/*
 * StartSymbol.h
 *
 *  Created on: 20 May 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_STARTSYMBOL_H_
#define SRC_INCLUDE_STARTSYMBOL_H_

#include "Token.h"

namespace lexer {

class StartSymbol: public Token {
public:
        StartSymbol(Lexer* p);
        virtual ~StartSymbol();

        virtual Token* omit_starter();
};

}

#endif /* SRC_INCLUDE_STARTSYMBOL_H_ */
