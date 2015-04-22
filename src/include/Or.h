/*
 * Or.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_OR_H_
#define SRC_OR_H_

#include "Automaton.h"

class Or : Automaton{
public:
        Or(std::string* rule);
        virtual ~Or();
};

#endif /* SRC_OR_H_ */
