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
                str->append("\" ];\n");
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

bool State::enforce(string& rule)
{
        if (rule.length() == 0) {
                return this->end_state;
        }

        if (this->error_state) {
                return false;
        }

        State* next = this->map_transitions[rule[0]];
        /* If letter not in alphabet! */
        if (next == NULL) {
                return false;
        }

        string sub_rule = rule.substr(1);
        return next->enforce(sub_rule);
}

void State::build_word(bool allowed, string* word, size_t len)
{
        if (len == 0) {
                return;
        }

        if (this->error_state) {
                if (allowed) {
                        return;
                }
        }

        if (this->get_end_state() && allowed) {
                cout << "Accepting word: " << *word << endl;
        } else if (!this->get_end_state() && !allowed) {
                cout << "Rejecting word: " << *word << endl;
        }

        Alphabet* alpha = Alphabet::get_alphabet();
        std::string* alpha_str = alpha->get_string();
        for (size_t i = 0; i < alpha->get_size(); i++) {
                string tmp_string = *word;
                char c = (*alpha_str)[i];

                tmp_string.push_back(c);

                this->map_transitions[c]->build_word(allowed, &tmp_string,
                                len - 1);
        }
}

} /* namespace DFA */
