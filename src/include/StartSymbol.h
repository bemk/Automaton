/*
 * StartSymbol.h
 *
 *  Created on: 20 May 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_STARTSYMBOL_H_
#define SRC_INCLUDE_STARTSYMBOL_H_

#include "Symbol.h"

class StartSymbol : public Symbol{
public:
        StartSymbol(Parser* p);
        virtual ~StartSymbol();
};

#endif /* SRC_INCLUDE_STARTSYMBOL_H_ */