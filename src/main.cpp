/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */
#include <iostream>
#include "include/Parser.h"

using namespace std;

int main(int argc, char** argv)
{
        if (argc < 3) {
                cerr << "Not enough arguments!" << endl;
        }

        cout << argv[1] << endl;
        cout << argv[2] << endl;

        Parser* p = new Parser(new string(argv[1]));
        p->parse(new string(argv[2]));

        return 0;
}

