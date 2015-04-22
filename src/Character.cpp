/*
 * Character.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Character.h"
#include "include/Capture.h"
#include <iostream>
#include <cstdlib>
using namespace std;

CharString::CharString(string* rule) :
                Automaton(rule)
{
        no_automatons = 0;

        CharString* char_chain = NULL;

        for (int i = 0; i < rule->length(); i++) {
                char c = rule->at(i);
                switch (c) {
                case ' ':
                        // This is a space, please ignore this
                        break;

                case '(': {
                        // Do some stuff with capture

                        string* s = new string(rule->substr(i));
                        Capture* cap = new Capture(s);
                        i += cap->length();
                        automatons[no_automatons] = cap;
                        no_automatons++;

                        delete s;
                }
                        break;

                case '|':
                        // Do some stuff with or operator
                        if (i == 0) {
                                // PANIC!!!
                                cerr << "Invalid operation detected!" << endl;
                                exit(-5);
                        } else {

                        }

                        break;

                default:
                        // Add to dictionary
                        if (char_chain == NULL) {
                        automatons[no_automatons] = this;
                        no_automatons++;

                        char_chain = this;
                        } else {
                                char_chain->appendCharacter(c);
                        }

                        break;
                }
        }
}

CharString::~CharString()
{
        // TODO Auto-generated destructor stub
}

void CharString::appendCharacter(char c)
{

}
