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

namespace NFA {
class State;
}

namespace DFA {

class IntState;
static IntState* errorState;

class IntState {
private:
        std::map<char, std::vector<NFA::State*>*> states;
        std::vector<NFA::State*> epsilon_state;

        std::vector<NFA::State*> destinations;

        bool endstate;
        bool startstate;

public:
        IntState(size_t size);
        virtual ~IntState();
        void build_error_transitions();
        void add_transition(NFA::State* dest, char c);
        IntState* get_error_state();
        bool compare(IntState* cmp);

        bool has_e_transition(NFA::State* destination);
        bool put_e_transition(NFA::State* destination);

        bool get_endstate();
        void set_endstate();

};

} /* namespace DFA */

#endif /* SRC_INCLUDE_INTSTATE_H_ */
