/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */
#include <iostream>
#include "include/Parser.h"
#include "include/Capture.h"
#include "include/wingetopt.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char** argv)
{

        int getoptoutput;
        char *ropt = 0;
        int repetition_depth = -1;
        while ((getoptoutput = getopt(argc, argv, "r:d:")) != -1) {
                switch (getoptoutput) {
                case 'r':
                        cout << "regex with value " << optarg << endl;
                        ropt = optarg;
                        break;
                case 'd':
                        repetition_depth = atoi(optarg);
                        if (repetition_depth == -1 || repetition_depth == 0) {
                                cerr << "Depth should be a positive integer"
                                     << endl;
                                exit(-1);
                        }
                        cout << "depth with value " << repetition_depth << endl;
                        break;
                default:
                        cerr << "getopt returned character code" << getoptoutput
                             << endl;
                        exit(-1);
                }
        }

        if (argc < 4) {
                cerr << "Not enough arguments!" << endl;
                exit(-1);
        }

        Parser* p = new Parser();
        p->build_grammar(new string(ropt));
        p->enforceGrammar(new string(ropt));

        delete p;

        return 0;
}

