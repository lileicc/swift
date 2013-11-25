/*
 * QualType.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "QualType.h"

namespace swift {
namespace code {

QualType::QualType(std::string name, bool refTag) : name(name), refTag(refTag) {
}

QualType::~QualType() {
}

std::string QualType::getName() {
  return name;
}

bool QualType::isRef() {
  return refTag;
}

} /* namespace code */
} /* namespace swift */
