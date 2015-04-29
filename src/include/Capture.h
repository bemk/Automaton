/*
 * Capture.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CAPTURE_H_
#define SRC_CAPTURE_H_

#include "Symbol.h"
#include "Parser.h"
#include "Quantifier.h"
#include <string>

class Capture: public Symbol {
private:
        Parser* nodes;
        Quantifier* quantifier;
        size_t str_length;

public:
        Capture();
        virtual ~Capture();

        virtual size_t build_grammar(std::string* rule, size_t location);
        size_t length();

        virtual bool isOfType(char);
        virtual Symbol* allocateType();
};

#endif /* SRC_CAPTURE_H_ */
