/*
 * QuestionMark.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "../include/QuestionMark.h"

using namespace std;

namespace lexer {

QuestionMark::QuestionMark(Parser* p) :
                Quantifier(p)
{
        this->start_at = START_NULL;
        this->stop_at = END_ONE;
        this->text = "?";
}

QuestionMark::~QuestionMark()
{
}

bool QuestionMark::isOfType(char c)
{
        return (c == '?') ? true : false;
}

Symbol* QuestionMark::allocateType()
{
        Symbol* s = new QuestionMark(this->parser);
        if (s == NULL) {
                cerr << "Unable to allocate questionmark descriptor" << endl;
                exit(-1);
        }
        return s;
}

}