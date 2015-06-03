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
#include "../include/Transition.h"

namespace NFA {

class Transition;

class Automaton {
private:
        bool graphed;
        size_t location;
        std::string name;
        std::vector<Transition*> transitions;
        std::vector<Transition*> incomming;
        int unique_id;

        void get_dot_reference(std::string* s, std::string* caller,
                        bool epsylon, char input);

        void add_incomming(Transition* incomming)
        {
                this->incomming.push_back(incomming);
        }

public:
        Automaton(size_t location, std::string name);
        virtual ~Automaton();

        void add_transition(char input, Automaton* destination);
        void add_epsilon(Automaton* destination);
        bool get_dotgraph(std::string* s);

        std::string* get_name();

        std::vector<Transition*>* get_transitions()
        {
                return &this->transitions;
        }

        std::vector<Transition*>* get_incomming()
        {
                return &this->incomming;
        }
};

} /* namespace NFA */

#endif /* SRC_NFA_AUTOMATON_H_ */
