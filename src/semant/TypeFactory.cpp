/*
 * TypeFactory.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#include "TypeFactory.h"

namespace swift {
namespace semant {
TypeFactory::TypeFactory() {
  // TODO Auto-generated constructor stub

}

TypeFactory::~TypeFactory() {
  // TODO Auto-generated destructor stub
}

bool TypeFactory::addNameTy(const std::string& str) {
  if (tyTable.find(str) != tyTable.end()) return false;
  tyTable[str] = new ir::NameTy(new ir::TypeDomain());
  return true;
}

}
} /* namespace swift */
