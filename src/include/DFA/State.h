/*
 * State.h
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_DFA_STATE_H_
#define SRC_INCLUDE_DFA_STATE_H_

#include "../NFA/State.h"
#include "../NFA/Transition.h"
#include <map>

namespace NFA {
class State;
}

namespace DFA {

class State: NFA::State {
private:
        std::map<char, State*> map_transitions;

        bool error_state;

public:
        State(size_t location, std::string name);
        virtual ~State();

        State* get_error();
        void set_error_state();

        void add_transition(char c, State* s);
};

} /* namespace DFA */

#endif /* SRC_INCLUDE_DFA_STATE_H_ */
