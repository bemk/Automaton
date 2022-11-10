/*
 * DFAState.h
 *
 *  Created on: 10 Nov 2022
 *      Author: bemk
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
    void generate_name();
public:
    DFA_State(std::vector<NFA::State*>& sources);
    DFA_State(size_t source, std::string name);
    virtual ~DFA_State();
};

} /* namespace DFA */

#endif /* SRC_DFA_DFASTATE_H_ */
