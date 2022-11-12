/*
 * DFAState.h
 *
 *  Created on: 10 Nov 2022
 *      Author: Bart Kuivenhoven
 */

#include <vector>
#include <string>
#include "../NFA/State.h"

#ifndef SRC_DFA_DFASTATE_H_
#define SRC_DFA_DFASTATE_H_

namespace DFA {

class DFA_State: public NFA::State {
private:
    std::vector<NFA::State*> sources;

    void add_source(NFA::State* state);
    void add_sources(std::vector<NFA::State*>&);
    void build_word(std::string path, size_t depth);
public:
    DFA_State(std::vector<NFA::State*>& sources, std::string name);
    virtual ~DFA_State();
    std::vector<NFA::State*> get_sources() {return sources;}
    void set_name(std::string name) {this->name = name;}

    bool enforce(const char* input);
    void build_word(size_t depth);
};

} /* namespace DFA */

#endif /* SRC_DFA_DFASTATE_H_ */
