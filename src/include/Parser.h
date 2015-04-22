/*
 * Parser.h
 *
 *  Created on: 22 Apr 2015
 *      Author: bemk
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <iostream>
#include <string>

class Parser {
public:
        Parser(std::string* rule);
        virtual ~Parser();

        int parse(std::string* line);
};

#endif /* SRC_PARSER_H_ */
