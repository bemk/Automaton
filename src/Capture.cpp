/*
 * Capture.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Capture.h"
#include <iostream>
using namespace std;

Capture::Capture(string* rule) : Automaton(rule)
{
        this->internal_string = new string();
        int depth_cnt = 0;
        for (string::iterator it = rule->begin(); it != rule->end(); it++) {
                char c = *it;
                switch (c) {
                case '(':
                        if (depth_cnt++ != 0) {
                                internal_string->append(string(c));
                        }
                        break;
                case ')':
                        if (--depth_cnt != 0) {
                                internal_string->append(string(c));
                        }
                        break;
                default:
                        internal_string->append(string(c));
                        break;
                }
        }

        // TODO Auto-generated constructor stub

}

Capture::~Capture()
{
        // TODO Auto-generated destructor stub
}

