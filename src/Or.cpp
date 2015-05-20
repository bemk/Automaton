/*
 * Or.cpp
 *
 *  Created on: 20 mei 2015
 *      Author: Thomas
 */

#include "include/Or.h"
#include <cstdlib>
using namespace std;

Or::Or()
{
        // TODO Auto-generated constructor stub

}

Or::~Or()
{
        // TODO Auto-generated destructor stub
}

size_t Or::build_grammar(string* s, size_t location)
{
        return 1;
}
bool Or::isOfType(char c)
{
        if (c == '|') {
                return true;
        }
        return false;
}

Symbol* Or::allocateType(void)
{
        Symbol* s = (Symbol*) new Or();
        if (s == NULL) {
                cerr << "NULL POINTER ALLOCATED" << endl;
                exit(-1);
        }
        return s;
}

