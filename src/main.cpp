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
bool reset_id_alloc = false;

bool verbose = false;
bool symbol_graph = false;
const char *symbol_name;

std::string graph_text = "digraph {\n";

bool NFA_graph = false;
const char *NFA_name;
std::string NFA_text = "digraph finite_state_machine {\nrankdir = LR;\n";

bool DFA_graph = false;
const char *DFA_name;
std::string DFA_text = "digraph finite_state_machine {\nrankdir = LR;\n";

bool enforce = false;
const char *enforcement_rule;
bool inverted = true;

void help()
{
#ifndef __GNUC__
        cout << "The help option doesn't work under windows!" << endl;
#endif
    system("less help.doc");
    exit(0);
}

void writeParseGraph(IGraphable* graphable, const char* file_name, const char* ropt)
{
    ofstream dot_file;
    dot_file.open(symbol_name);

    string sym_text = "";
    graphable->get_dot_graph(&sym_text);
    graph_text.append(sym_text);

    graph_text.append("label=\"");
    graph_text.append(ropt);
    graph_text.append("\";\nlabelloc=top\n");

    graph_text.push_back('}');

    dot_file << graph_text << endl;
    dot_file.close();
}

void writeStateDiagram(NFA::State* start, vector<NFA::State*> end, const char* file_name, const char* ropt, std::string top_text) {
    ofstream dot_file;
    dot_file.open(file_name);
    string node_text = "";

    start->get_dot_graph(&node_text);

    node_text.append("label=\"");
    node_text.append(ropt);
    node_text.append("\";\nlabelloc=top;\n");

    node_text.append("}\n");

    if (end.size() > 0) {

        top_text.append("node [shape = doublecircle]; ");
        for (NFA::State* accept : end) {
            top_text.append(*accept->get_name());
            top_text.append(";\n");
        }
    }

    top_text.append("node [shape = circle];\n");
    top_text.append(node_text);
    dot_file <<  top_text << endl;
    dot_file.close();
}

int main(int argc, char **argv)
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
                cerr << "Depth should be a positive integer" << endl;
                exit(-1);
            }
            break;

        case 'v':
            verbose = true;
            break;

        case 'g':
            symbol_graph = true;
            symbol_name = optarg;
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
            cerr << "getopt returned character code" << getoptoutput << endl;
            exit(-1);
        }
    }

    if (verbose) {
        cout << "regex with value " << ropt << endl;
        cout << "depth with value " << repetition_depth << endl;
    }
    /* Start interpreting the regular expression */
    Lexer::Lexer *p = new Lexer::Lexer(0);
    p->build_grammar(new string(ropt));
    p->enforceGrammar(new string(ropt));

    /* Get the tokens */
    Lexer::Token *symbols = p->get_tokens();
    symbols->set_parser(NULL);

    /* Remove the main Lexer */
    delete p;

    if (verbose) {
        Alphabet *alpha = Alphabet::get_alphabet();
        cout << "Alphabet is: '" << *alpha->get_string() << "'" << endl;
    }

    /* If requested, write a dot-graph for the regular expression */
    if (symbol_graph) {
        writeParseGraph(symbols, symbol_name, ropt);
    }

    /*
     * Generate the NFA and mark the accepting state as such
     */
    symbols->get_ll_next()->get_accept_symbol()->set_end_state(true);

    /* Build a dot graph for the NFA if requested */
    if (NFA_graph) {
        NFA::State* start = symbols->get_ll_next()->get_start_symbol();
        NFA::State* end = symbols->get_ll_next()->get_accept_symbol();
        std::vector<NFA::State*> ends = std::vector<NFA::State*>();
        ends.push_back(end);
        writeStateDiagram(start, ends, NFA_name, ropt, NFA_text);
    }

    /* Generate the DFA */
    reset_id_alloc = true;
    DFA::Parser parser = DFA::Parser(symbols->get_ll_next()->get_start_symbol());

    NFA::State* dfa = parser.build_DFA();
    if (DFA_graph) {
        std::vector<NFA::State*> ends = parser.get_end_states();
        writeStateDiagram(dfa, ends, DFA_name, ropt, DFA_text);
    }

    if (enforce) {
        if (((DFA::DFA_State*)dfa)->enforce(enforcement_rule)) {
            cout << "Rule '" << enforcement_rule << "' matched!" << endl;
        } else {
            cout << "Rule '" << enforcement_rule << "' did not match!" << endl;
        }
    }

#ifndef __GNUC__
        system("PAUSE");
#endif
    return 0;
}

