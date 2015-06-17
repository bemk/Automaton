/*
 * State.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: bemk
 */

#include "../include/DFA/State.h"
#include "../include/Alphabet.h"
#include <sstream>
#include <cstdlib>

using namespace std;

namespace DFA {

static int unique_id_alloc = 0;

static State* global_error_state = NULL;

State::State(size_t location, string name, bool redundant) :
                NFA::State(location, name)
{
        stringstream name_str;
        name_str << "q_" << unique_id_alloc++;

        this->name = name_str.str();

        error_state = false;
        this->map_transitions = map<char, State*>();

}

State::State(size_t location, string name) :
                NFA::State(location, name)
{
        stringstream name_str;
        name_str << "q_" << unique_id_alloc++;

        this->name = name_str.str();

        error_state = false;
        this->map_transitions = map<char, State*>();

        Alphabet* alpha = Alphabet::get_alphabet();

        for (int idx = 0; idx < alpha->get_string()->size(); idx++) {
                char c = alpha->get_string()->at(idx);

                this->map_transitions[c] = this->get_error();
        }
}

void State::reset_error()
{
        Alphabet* alpha = Alphabet::get_alphabet();
        for (int idx = 0; idx < alpha->get_string()->size(); idx++) {
                char c = alpha->get_string()->at(idx);

                this->map_transitions[c] = this->get_error();
        }
}

State::~State()
{
}

void State::add_transition(char c, State* s)
{
        if (s == NULL) {
                cerr << "Oh shit!" << endl;
        }
        this->map_transitions[c] = s;
}

void State::set_error_state()
{
        this->error_state = true;
        this->name = "q_error";
}

State* State::get_error()
{
        if (global_error_state == NULL) {
                global_error_state = new State(0, "ERROR", true);
                global_error_state->reset_error();
                global_error_state->set_error_state();
        }
        return global_error_state;
}

void State::get_dot_graph(std::string* str, std::string* end_claim)
{
        if (this->graphed) {
                return;
        }
        graphed = true;

        Alphabet* alpha = Alphabet::get_alphabet();

        if (this->error_state) {
                str->append(this->name);
                str->append(" -> ");
                str->append(this->name);
                str->append(" [ label = \"");
                str->append(*alpha->get_string());
                str->append("\" ];");
                return;
        }

        for (size_t idx = 0; idx < alpha->get_size(); idx++) {
                char c = (*alpha->get_string())[idx];
                State* s = this->map_transitions[c];
                if (s == NULL) {
                        cerr << "Ayeeee!!!!!" << endl;
                        exit(-9005);
                }

                if (this->get_end_state()) {
                        end_claim->append(this->name);
                        end_claim->append("[shape = doublecircle ];\n");
                }
                str->append(this->name);
                str->append(" -> ");
                str->append(*s->get_name());
                str->append(" [label=\"");
                str->push_back(c);
                str->append("\"];\n");

                s->get_dot_graph(str, end_claim);
        }
}

} /* namespace DFA */
