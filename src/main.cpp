/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */
#include <iostream>
#include <fstream>
#include "include/Capture.h"
#include "include/wingetopt.h"
#include "include/Alphabet.h"
#include <cstdlib>
#include <cstdio>
#include "include/Lexer.h"
#include "include/DFA/Parser.h"

using namespace std;

bool simple_graph = false;

bool verbose = false;
bool dot_graph = false;
const char* dotname;

std::string graph_text = "digraph {\n";

bool NFA_graph = false;
const char* NFA_name;
std::string NFA_text = "digraph finite_state_machine {\nrankdir = LR;\n";

bool DFA_graph = false;
const char* DFA_name;
std::string DFA_text = "digraph finite_state_machine {\nrankdir = LR;\n";

bool enforce = false;
const char* enforcement_rule;
bool inverted = true;

void help()
{
#ifndef __GNUC__
        cout << "The help option doesn't work under windows!" << endl;
#endif
        system("less help.doc");
        exit(0);
}

int main(int argc, char** argv)
{
        /* Do options parsing */
        int getoptoutput;
        char *ropt = 0;
        int repetition_depth = -1;
        while ((getoptoutput = getopt(argc, argv, "r:d:vg:n:sho:e:i")) != -1) {
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

                case 'n':
                        NFA_graph = true;
                        NFA_name = optarg;

                        break;
                case 's':
                        simple_graph = true;
                        break;
                case 'h':
                        help();
                        break;
                case 'o':
                        DFA_graph = true;
                        DFA_name = optarg;
                        break;
                case 'e':
                        enforce = true;
                        enforcement_rule = optarg;
                        break;
                case 'i':
                        inverted = false;
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
        /* Start interpreting the regular expression */
        lexer::Lexer* p = new lexer::Lexer(0);
        p->build_grammar(new string(ropt));
        p->enforceGrammar(new string(ropt));

        /* Get the tokens */
        lexer::Token* symbols = p->get_tokens();
        symbols->set_parser(NULL);

        /* Remove the main lexter */
        delete p;

        if (verbose) {
                Alphabet* alpha = Alphabet::get_alphabet();
                cout << "Alphabet is: '" << *alpha->get_string() << "'" << endl;
        }

        /* If requested, write a dot-graph for the regular expression */
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

        /*
         * Generate the NFA and mark the accepting state as such
         */
        symbols->get_ll_next()->get_accept_symbol()->set_end_state(true);

        /* Build a dot graph for the NFA if requested */
        if (NFA_graph) {
                ofstream dot_file;
                dot_file.open(NFA_name);
                string node_text = "";

                symbols->get_ll_next()->get_start_symbol()->get_dotgraph(
                                &node_text);

                node_text.append("label=\"");
                node_text.append(ropt);
                node_text.append("\";\nlabelloc=top\n");

                node_text.push_back('}');

                NFA::State* accept =
                                symbols->get_ll_next()->get_accept_symbol();

                NFA_text.append("node [shape = doublecircle]; ");
                NFA_text.append(*accept->get_name());
                NFA_text.append(" ;\nnode [shape = circle];\n");

                NFA_text.append(node_text);

                dot_file << NFA_text << endl;
                dot_file.close();
        }

        /* Build a parser for the NFA */
        DFA::Parser parser = DFA::Parser(symbols->get_ll_next());
        /* Buid a DFA out of the NFA */
        parser.parse();

        /* Get the DFA reference */
        DFA::State* dfa = parser.get_dfa();

        /* Build a DFA dot graph if requested. */
        if (DFA_graph) {
                ofstream dot_file;
                dot_file.open(DFA_name);
                string node_text = "";
                string end_claim = "";

                dfa->get_dot_graph(&node_text, &end_claim);
                end_claim.append("node [shape = circle];");

                node_text.append("label=\"");
                node_text.append(ropt);
                node_text.append("\";\nlabelloc=top\n");
                node_text.append("\"\" [ shape=\"none\"]; \"\" -> q_0;");
                node_text.push_back('}');

                DFA_text.append(end_claim);
                DFA_text.append(node_text);

                dot_file << DFA_text << endl;
                dot_file.close();
        }

        /* If requested, see if input string matches rules */
        if (enforce) {
                string rule = string(enforcement_rule);
                if (dfa->enforce(rule)) {
                        cout << "Rule accepted!" << endl;
                } else {
                        cout << "Rule denied!" << endl;
                }
        }

        if (repetition_depth > 0) {
        	string str = "";
        	dfa->build_word(inverted, &str, repetition_depth);
        }

#ifndef __GNUC__
        system("PAUSE");
#endif
        return 0;
}

