/*

 *
 *  Created on: 29 May 2015
 *      Author: bemk
 */

#ifndef SRC_NFA_AUTOMATON_H_
#define SRC_NFA_AUTOMATON_H_

#include <string>
#include <iostream>

namespace NFA {

class Automaton {
private:
        size_t location;
        std::string name;

public:
        Automaton(size_t location, std::string name);
        virtual ~Automaton();
};

} /* namespace NFA */

#endif /* SRC_NFA_AUTOMATON_H_ */
