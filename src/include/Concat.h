/*
 * Concat.h
 *
 *  Created on: 29 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CONCAT_H_
#define SRC_CONCAT_H_

#include "Symbol.h"

class Concat : public Symbol {
public:
        Concat();
        virtual ~Concat();

        bool isOfType(char c);

};

#endif /* SRC_CONCAT_H_ */
