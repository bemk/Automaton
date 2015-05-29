/*
 * Transition.h
 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_TRANSITION_H_
#define SRC_INCLUDE_TRANSITION_H_

#include "Automaton.h"

namespace NFA {

class Transition {
private:
        char symbol;
        size_t location;

        Automaton* source;
        Automaton* dest;

        void init(size_t location, char symbol, Automaton* source,
                        Automaton* dest);

public:
        Transition(size_t location, char symbol, Automaton* source,
                        Automaton* dest);
        Transition(size_t location);
        virtual ~Transition();

        void set_symbol(char symbol);

        void set_source(Automaton* source);
        void set_dest(Automaton* dest);

        char get_symbol();

        Automaton* get_source();
        Automaton* get_dest();
};

} /* namespace NFA */

#endif /* SRC_INCLUDE_TRANSITION_H_ */
