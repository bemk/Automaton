/*
 * Parser.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#include "../include/Lexer.h"

#include "../include/Capture.h"
#include "../include/Concat.h"
#include "../include/QuestionMark.h"
#include "../include/Plus.h"
#include "../include/Star.h"
#include "../include/Or.h"
#include <cstdlib>
#include "../include/StartToken.h"

using namespace std;

extern bool verbose;

namespace lexer {

Lexer::Lexer(size_t location)
{
        this->location = location;
        symbol_tree = NULL;
        symbolTypes = vector<Token*>();

        symbolTypes.push_back((Token*) new Star(this));
        symbolTypes.push_back((Token*) new QuestionMark(this));
        symbolTypes.push_back((Token*) new Plus(this));
        symbolTypes.push_back((Token*) new Capture(this));
        symbolTypes.push_back((Token*) new Concat(this));
        symbolTypes.push_back((Token*) new Or(this));
        symbolTypes.push_back((Token*) new Token(this));

}

Lexer::~Lexer()
{
        symbolTypes.clear();
}

Token* Lexer::get_symbols()
{
        return this->symbol_tree;
}

void Lexer::set_symbols(Token* s)
{
        this->symbol_tree = new StartToken(this);
        this->symbol_tree->set_concatenation(false);
        this->symbol_tree->set_location(this->location);
        this->symbol_tree->set_ll_next(s);
        s->set_ll_prev(this->symbol_tree);
}

void insert_concats(Token* sym, Lexer* p)
{
        for (; sym != NULL; sym = sym->get_ll_next()) {
                if (verbose) {
                        cout << *sym->getString() << endl;
                }

                Token* next = sym->get_ll_next();

                if (sym->getLeft()) {
                        insert_concats(sym->getLeft(), p);
                }

                if (next == NULL) {
                        break;
                }

                if (next->concatenation_allowed() && sym->concatenation_allowed()) {
                        Token* concat = new Concat(p);
                        concat->set_ll_prev(sym);
                        concat->set_ll_next(next);
                        concat->set_location(sym->get_location());
                        sym->set_ll_next(concat);
                        next->set_ll_prev(concat);
                }
        }
}

int Lexer::build_grammar(string* rule)
{
        this->symbol_tree = new StartToken(this);
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

                Token* sym = this->symbol_tree->get_ll_last();

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

        set_symbols(get_symbols()->omit_starter());

        /* Second pass, Dump the symbols! (for now) */

        insert_concats(get_symbols(), this);
        get_symbols()->do_concatenate();

        return 0;
}

int Lexer::enforceGrammar(string* line)
{
        return 0;
}

}

