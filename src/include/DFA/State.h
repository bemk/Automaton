/*
 * State.h
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_DFA_STATE_H_
#define SRC_INCLUDE_DFA_STATE_H_

#include "../NFA/State.h"
#include <vector>

namespace DFA {

class State: NFA::State {
private:
        std::vector<NFA::State*> sources;
        std::vector<Transition> transitions;

public:
        State(size_t location, std::string name);
        virtual ~State();
};

} /* namespace DFA */

#endif /* SRC_INCLUDE_DFA_STATE_H_ */
