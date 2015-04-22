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
	int cnt = 0;
	for (string::iterator it = rule->begin(); it != rule->end(); ++it, cnt++) {
		char c = *it;
		switch (c) {
		case '(':
			if (depth_cnt++ != 0) {
				internal_string->push_back(c);
			}
			break;
		case ')':
			depth_cnt--;
			if (depth_cnt != 0) {
				internal_string->push_back(c);
			} else {
				string s = string(rule->substr(cnt+1, rule->length()));
				quantifier = new Quantifier(&s);
				goto end_of_loop;
			}
			break;
		default:
			internal_string->push_back(c);
			break;

		}
	}
	
end_of_loop:
	cout << "Captured: " << *internal_string << endl;
	nodes = new Automaton(internal_string);
}

Capture::~Capture()
{
	// TODO Auto-generated destructor stub
}

