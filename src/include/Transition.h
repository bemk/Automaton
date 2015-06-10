/*
 * Transition.h
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_TRANSITION_H_
#define SRC_INCLUDE_TRANSITION_H_

#include "State.h"

namespace NFA {

class State;

class Transition {
private:
        char symbol;
        size_t location;

        State* source;
        State* dest;

        bool epsilon;

        void init(size_t location, char symbol, State* source,
                        State* dest);

public:
        Transition(size_t location, char symbol, State* source,
                        State* dest);
        Transition(size_t location);
        virtual ~Transition();

        void set_symbol(char symbol);

        void set_source(State* source);
        void set_dest(State* dest);

        void set_epsilon(bool epsylon);

        char get_symbol();

        State* get_source();
        State* get_dest();

        bool get_epsilon();

};

} /* namespace NFA */

#endif /* SRC_INCLUDE_TRANSITION_H_ */
