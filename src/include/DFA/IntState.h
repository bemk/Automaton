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

class State;

class IntState {
private:
        std::map<char, std::vector<NFA::State*>*> states;
        std::vector<NFA::State*> epsilon_state;

        std::vector<NFA::State*> destinations;

        std::vector<char> local_alphabet;

        bool endstate;
        bool startstate;

        State* DFA_State;
public:
        IntState(size_t size);
        virtual ~IntState();
        void add_transition(NFA::State* dest, char c);

        bool has_e_transition(NFA::State* destination);
        bool put_e_transition(NFA::State* destination);

        bool get_endstate();
        void set_endstate();

        void build_int_states();
        State* build_dfa_state();
};

} /* namespace DFA */

#endif /* SRC_INCLUDE_INTSTATE_H_ */
