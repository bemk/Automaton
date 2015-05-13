/*
 * QuestionMark.cpp
 *
 *  Created on: 13 mei 2015
 *      Author: Thomas
 */

#include "include/QuestionMark.h"

QuestionMark::QuestionMark()
{
        this->start_at = START_NULL;
        this->stop_at = END_ONE;

}

QuestionMark::~QuestionMark()
{
        // TODO Auto-generated destructor stub
}

bool QuestionMark::isOfType(char c)
{
        return (c == '?') ? true : false;
}

