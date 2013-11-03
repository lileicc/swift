/*
 * Symbol.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "Symbol.h"

namespace swift {
namespace absyn {

Symbol::Symbol(std::string v) :
    value(v) {
}

Symbol::~Symbol() {
}

const std::string& Symbol::getValue() {
  return value;
}

}
}
