/*
 * IGraphable.h
 *
 *  Created on: 9 Nov 2022
 *      Author: bemk
 */

#ifndef SRC_INCLUDE_IGRAPHABLE_H_
#define SRC_INCLUDE_IGRAPHABLE_H_

#include <string>

class IGraphable {
public:
    virtual bool get_dot_graph(std::string*) = 0;
};

#endif /* SRC_INCLUDE_IGRAPHABLE_H_ */
