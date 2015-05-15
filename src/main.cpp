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
#include "include/Alphabet.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

bool verbose = false;

int main(int argc, char** argv)
{

        int getoptoutput;
        char *ropt = 0;
        int repetition_depth = -1;
        while ((getoptoutput = getopt(argc, argv, "r:d:v")) != -1) {
                switch (getoptoutput) {
                case 'r':
                        ropt = optarg;
                        break;

                case 'd':
                        repetition_depth = atoi(optarg);
                        if (repetition_depth == -1 || repetition_depth == 0) {
                                cerr << "Depth should be a positive integer"
                                     << endl;
                                exit(-1);
                        }
                        break;

                case 'v':
                        verbose = true;
                        break;

                default:
                        cerr << "getopt returned character code" << getoptoutput
                             << endl;
                        exit(-1);
                }
        }

        if (verbose) {
                cout << "regex with value " << ropt << endl;
                cout << "depth with value " << repetition_depth << endl;
        }

        Parser* p = new Parser(0);
        p->build_grammar(new string(ropt));
        p->enforceGrammar(new string(ropt));

        Symbol* symbols = p->getSymbols();

        delete p;

        Alphabet* alpha = Alphabet::get_alphabet();
        cout << "Alphabet is : '" << *alpha->get_string() << "'" << endl;

        return 0;
}

