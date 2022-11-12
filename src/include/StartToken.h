/*
 * StartSymbol.h
 *
 *  Created on: 20 May 2015
 *      Author: Thomas Moors & Bart Kuivenhoven
 */

#ifndef SRC_INCLUDE_STARTTOKEN_H_
#define SRC_INCLUDE_STARTTOKEN_H_

#include "Token.h"

namespace Lexer {

class StartToken: public Token {
public:
        StartToken(Lexer* p);
        virtual ~StartToken();

        virtual Token* omit_starter();
};

}

#endif /* SRC_INCLUDE_STARTTOKEN_H_ */
