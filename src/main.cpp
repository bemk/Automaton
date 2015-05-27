/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */
#include <iostream>
#include <fstream>
#include "include/Parser.h"
#include "include/Capture.h"
#include "include/wingetopt.h"
#include "include/Alphabet.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

bool verbose = false;
bool dot_graph = false;
const char* dotname;

std::string graph_text = "digraph {\n";

int main(int argc, char** argv)
{
        int getoptoutput;
        char *ropt = 0;
        int repetition_depth = -1;
        while ((getoptoutput = getopt(argc, argv, "r:d:vg:")) != -1) {
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

                case 'g':
                        dot_graph = true;
                        dotname = optarg;
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

        Symbol* symbols = p->get_symbols();
        symbols->set_parser(NULL);

        delete p;

        if (verbose) {
                Alphabet* alpha = Alphabet::get_alphabet();
                cout << "Alphabet is: '" << *alpha->get_string() << "'" << endl;
        }

        if (dot_graph) {
                ofstream dot_file;
                dot_file.open(dotname);

                string sym_text = "";
                symbols->get_dot_graph(&sym_text);
                graph_text.append(sym_text);

                graph_text.append("label=\"");
                graph_text.append(ropt);
                graph_text.append("\";\nlabelloc=top\n");

                graph_text.push_back('}');

                dot_file << graph_text << endl;
                dot_file.close();
        }

#ifndef __GNUC__
        system("PAUSE");
#endif
        return 0;
}

