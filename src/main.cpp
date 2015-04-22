/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */
#include <iostream>
#include "include/Automaton.h"

using namespace std;

int main(int argc, char** argv)
{
        if (argc < 2) {
                cerr << "Not enough arguments!" << endl;
        }

        cout << argv[1] << endl;

        return 0;
}

