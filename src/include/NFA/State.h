/*

 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#ifndef SRC_NFA_AUTOMATON_H_
#define SRC_NFA_AUTOMATON_H_

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include "Transition.h"
#include "../DFA/IntState.h"

namespace DFA {
class IntState;
}

namespace NFA {

class Transition;

class State {
protected:
        bool graphed;
        bool end_state;
        size_t location;
        std::string name;
        std::vector<Transition*> transitions;
        std::vector<Transition*> incoming;
        int unique_id;

        void get_dot_reference(std::string* s, std::string* caller,
                        bool epsylon, char input);

        void add_incoming(Transition* incoming)
        {
                this->incoming.push_back(incoming);
        }

        DFA::IntState* closure;

public:
        State(size_t location, std::string name);
        virtual ~State();

        void add_transition(char input, State* destination);
        void add_epsilon(State* destination);
        bool get_dotgraph(std::string* s);
        void set_end_state(bool end_state);
        bool get_end_state();

        std::string* get_name();

        std::vector<Transition*>* get_transitions()
        {
                return &this->transitions;
        }

        std::vector<Transition*>* get_incoming()
        {
                return &this->incoming;
        }

        DFA::IntState* build_closure_state(bool is_epsilon);
        void build_closure_state(DFA::IntState* closure);
        void build_DFA_state();
        State* get_DFA_state();

        DFA::IntState* get_closure();
        void set_closure(DFA::IntState* closure);
};

} /* namespace NFA */

#endif /* SRC_NFA_AUTOMATON_H_ */
