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
protected:
        std::string* internal_string;
public:
        Automaton(std::string* rule);
        virtual ~Automaton();

        int parse(std::string* line, int max_depth);
};

#endif /* SRC_AUTOMATON_H_ */
