/*
 * IntState.h

 *
 *  Created on: 16 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_INTSTATE_H_
#define SRC_INCLUDE_INTSTATE_H_

#include <vector>
#include <iostream>
#include <map>
#include "../NFA/State.h"

namespace DFA {

class IntState;
static IntState* errorState;

class IntState {
private:
        std::map<char, std::vector<IntState*>*> states;
        std::vector<IntState*> epsilon_state;

public:
        IntState(size_t size);
        virtual ~IntState();

        void build_error_transitions();

        void add_transition(IntState* dest, char c);

        IntState* get_error_state();
};

} /* namespace DFA */

#endif /* SRC_INCLUDE_INTSTATE_H_ */
