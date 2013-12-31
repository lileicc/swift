/*
 * Type.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Type.h"

namespace swift {
namespace code {

Type::Type(std::string name, bool refTag) : name(name), refTag(refTag) {
}

Type::~Type() {
}

std::string Type::getName() {
  return name;
}

bool Type::isRef() {
  return refTag;
}

} /* namespace code */
} /* namespace swift */
