/*
 * Capture.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CAPTURE_H_
#define SRC_CAPTURE_H_

#include "Automaton.h"

class Capture : Automaton {
public:
        Capture(std::string* rule);
        virtual ~Capture();
};

#endif /* SRC_CAPTURE_H_ */
