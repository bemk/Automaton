/*
 * Automaton.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_AUTOMATON_H_
#define SRC_AUTOMATON_H_

#include <string>

class Automaton {
private:
        std::string rule;
public:
        Automaton(std::string rule);
        virtual ~Automaton();
};

#endif /* SRC_AUTOMATON_H_ */
