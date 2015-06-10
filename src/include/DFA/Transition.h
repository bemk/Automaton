/*
 * Transition.h
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#ifndef SRC_DFA_TRANSITION_H_
#define SRC_DFA_TRANSITION_H_

#include "../NFA/Transition.h"

namespace DFA {

class Transition: NFA::Transition {
public:
        Transition(size_t location, char character, NFA::State* source,
                        NFA::State* dest);
        virtual ~Transition();

        virtual void set_epsilon(bool epsilon)
        {
                return;
        }

        virtual bool get_epsilon()
        {
                return false;
        }

};

} /* namespace DFA */

#endif /* SRC_DFA_TRANSITION_H_ */
