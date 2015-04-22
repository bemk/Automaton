/*
 * Character.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "Automaton.h"
#include "Quantifier.h"

class CharString: public Automaton{
private:
        Quantifier* quantifier;

        Automaton* automatons[3];

        CharString* child;
        size_t no_automatons;
        char character;

protected:

public:
        CharString(std::string* rule);
        virtual ~CharString();

        void appendCharacter(char c);
};

#endif /* SRC_CHARACTER_H_ */
