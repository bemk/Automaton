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
#include <map>
#include "Transition.h"
#include "../IGraphable.h"

namespace DFA {
class IntState;
}

namespace NFA {

class Transition;

class State : public IGraphable {
protected:
        bool graphed;
        bool end_state;
        bool parsed;
        size_t location;
        std::string name;
        std::vector<Transition*> transitions;
        std::vector<Transition*> incoming;

        std::map<char, std::vector<State*>> transition_map = std::map<char, std::vector<State*>>();
        int unique_id;

        void get_dot_reference(std::string* s, std::string* caller,
                        bool epsylon, char input);

        void add_incoming(Transition* incoming)
        {
                this->incoming.push_back(incoming);
        }

        DFA::IntState* closure;
        std::vector<NFA::State*>* get_states_for(char c, std::vector<NFA::State*>* seen);
        bool includes_end_state(std::vector<NFA::State*>& seen);

public:
        State(size_t location, std::string name);
        virtual ~State();

        void add_transition(char input, State* destination);
        void add_epsilon(State* destination);
        bool get_dot_graph(std::string* s) override;
        void set_end_state(bool end_state);
        bool includes_end_state();

        std::string* get_name();

        void get_all_character_transitions(std::map<char, std::vector<State*>>& transitions, std::vector<NFA::State*>& seen);

        std::vector<Transition*>* get_incoming()
        {
                return &this->incoming;
        }

        void mark_parsed() {this->parsed = true;}
        bool is_parsed() {return this->parsed;}
        size_t get_location() {return this->location;}

        std::vector<NFA::State*>* get_states_for(char c);
};

} /* namespace NFA */

#endif /* SRC_NFA_AUTOMATON_H_ */
