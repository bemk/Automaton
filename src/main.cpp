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
        int dopt = -1;
        while ((getoptoutput = getopt(argc, argv, "r:d:")) != -1) {
                switch (getoptoutput) {
                case 'r':
                        printf("regex with value '%s'\n", optarg);
                        ropt = optarg;
                        break;
                case 'd':
                        dopt = atoi(optarg);
                        if (dopt = -1)
                                cerr << "Depth should be a positive integer"
                                     << endl;
                        printf("depth with value '%d'\n", dopt);
                        break;
                default:
                        printf("?? getopt returned character code 0%o ??\n",
                                        getoptoutput);
                }
        }

        if (argc < 4) {
                cerr << "Not enough arguments!" << endl;
                exit(-1);
        }

        int repetition_depth = atoi(argv[1]);

        cout << argv[1] << endl;
        cout << argv[2] << endl;
        cout << argv[3] << endl;

        Parser* p = new Parser();
        p->build_grammar(new string(argv[2]));
        p->enforceGrammar(new string(argv[3]));

        /*
         for (int i = 0; i < size; i++) {
         cout << list[i] << endl;
         }
         */

        delete p;

        return 0;
}

