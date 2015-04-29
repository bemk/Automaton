/*
 * Parser.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Parser.h"
#include "include/Quantifier.h"
#include "include/Capture.h"
#include "include/Concat.h"
#include <cstdlib>

using namespace std;

Parser::Parser()
{
        symbol_tree = NULL;
        symbolTypes = vector<Symbol*>();

        symbolTypes.push_back((Symbol*) new Capture());
        symbolTypes.push_back((Symbol*) new Quantifier());
        symbolTypes.push_back((Symbol*) new Concat());
        symbolTypes.push_back(new Symbol());
}

Parser::~Parser()
{
}

int Parser::build_grammar(string* rule)
{
        Symbol* symbols = new Symbol();
        Symbol* sym = symbols;
        cout << "sizeof char " << sizeof(char) << endl;
        /* First pass, turn everything into symbols */
        for (int i = 0; i < rule->length();) {
                char c = rule->at(i);
                cout << "Parsing: '" << c << "'" << endl;
                if (c == ' ' || c == '\t') {
                        /* Skip white spaces */
                        i++;
                        continue;
                }



                for (int x = 0; x < symbolTypes.size(); x++) {
                        if (symbolTypes[x]->isOfType(c)) {
                                /* Let the symbol parser take over */

                                sym->set_ll_next(
                                                symbolTypes[x]->allocateType());
                                sym->get_ll_next()->set_ll_prev(sym);
                                sym = sym->get_ll_next();

                                /* The number of characters to skip */
                                size_t advance;

                                string* tmp = new string(rule->substr(i));
                                advance = sym->build_grammar(tmp);
                                delete tmp;

                                if (advance == 0) {
                                        cerr << "Fault in processing grammar!"
                                             << endl;
                                        exit(-5);
                                }
                                i += advance;
                                break;
                        }
                }
        }

        /* Second pass, turn the symbol list into a symbol tree */

        return 0;
}

int Parser::enforceGrammar(string* line)
{

        return 0;
}

