/*
 * Capture.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CAPTURE_H_
#define SRC_CAPTURE_H_

#include "Automaton.h"
#include "Quantifier.h"
#include <string>

class Capture: public Automaton {
private:
        Automaton* nodes;
        Quantifier* quantifier;
        size_t a_length;

public:
        Capture(std::string* rule);
        virtual ~Capture();
        size_t length();
};

#endif /* SRC_CAPTURE_H_ */
