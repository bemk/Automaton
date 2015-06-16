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
protected:
        char token;
        size_t location;

        State* source;
        State* dest;

        bool epsilon;

        void init(size_t location, char symbol, State* source, State* dest);

public:
        Transition(size_t location, char symbol, State* source, State* dest);
        Transition(size_t location);
        virtual ~Transition();

        void set_token(char symbol);

        void set_source(State* source);
        void set_dest(State* dest);

        virtual void set_epsilon(bool epsylon);
        virtual bool get_epsilon();

        char get_token();

        State* get_source();
        State* get_dest();

};

} /* namespace NFA */

#endif /* SRC_INCLUDE_TRANSITION_H_ */
