/*
 * Parser.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "include/Parser.h"
#include "include/Capture.h"
#include "include/Concat.h"
#include "include/QuestionMark.h"
#include "include/Plus.h"
#include "include/Star.h"
#include "include/StartSymbol.h"
#include "include/Or.h"
#include <cstdlib>

using namespace std;

extern bool verbose;

Parser::Parser(size_t location)
{
        this->location = location;
        symbol_tree = NULL;
        symbolTypes = vector<Symbol*>();

        symbolTypes.push_back((Symbol*) new Star(this));
        symbolTypes.push_back((Symbol*) new QuestionMark(this));
        symbolTypes.push_back((Symbol*) new Plus(this));
        symbolTypes.push_back((Symbol*) new Capture(this));
        symbolTypes.push_back((Symbol*) new Concat(this));
        symbolTypes.push_back((Symbol*) new Or(this));
        symbolTypes.push_back((Symbol*) new Symbol(this));

}

Parser::~Parser()
{
        symbolTypes.clear();
}

Symbol* Parser::get_symbols()
{
        return this->symbol_tree;
}

void Parser::set_symbols(Symbol* s)
{
        this->symbol_tree = new StartSymbol(this);
        this->symbol_tree->set_concatenation(false);
        this->symbol_tree->set_location(this->location);
        this->symbol_tree->set_ll_next(s);
        s->set_ll_prev(this->symbol_tree);
}

int Parser::build_grammar(string* rule)
{
        this->symbol_tree = new StartSymbol(this);
        this->symbol_tree->set_location(this->location);
        this->symbol_tree->set_concatenation(false);
        if (verbose) {
                cout << "sizeof char " << sizeof(char) << endl;
        }
        /* First pass, turn everything into symbols */
        for (size_t i = 0; i < rule->length();) {
                char c = rule->at(i);
                if (verbose) {
                        cout << "Parsing: '" << c << "'" << endl;
                }
                if (c == ' ' || c == '\t') {
                        /* Skip white spaces */
                        i++;
                        continue;
                }

                Symbol* sym = this->symbol_tree->get_ll_last();

                for (size_t x = 0; x < symbolTypes.size(); x++) {
                        if (symbolTypes[x]->isOfType(c)) {
                                /* Let the symbol parser take over */
                                sym->set_ll_next(
                                                symbolTypes[x]->allocateType());
                                sym->get_ll_next()->set_ll_prev(sym);
                                sym = sym->get_ll_next();

                                /* The number of characters to skip */
                                size_t advance;

                                string* tmp = new string(rule->substr(i));
                                advance = sym->build_grammar(tmp,
                                                this->location + i + 1);
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

        /* Second pass, Dump the symbols! (for now) */

        Symbol* sym = get_symbols();
        for (; sym != NULL; sym = sym->get_ll_next()) {
                if (verbose) {
                        cout << *sym->getString() << endl;
                }
        }

        return 0;
}

int Parser::enforceGrammar(string* line)
{
        return 0;
}
