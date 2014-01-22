/*
 * TemplatedType.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: leili
 */

#include "TemplatedType.h"

namespace swift {
namespace code {

TemplatedType::TemplatedType(Expr* scope, std::string name, std::vector<Type> typeArgs, bool refTag) : Type(scope, name, refTag), typeArgs(typeArgs) {
}
  
  TemplatedType::TemplatedType(std::string name, std::vector<Type> typeArgs, bool refTag) : TemplatedType(nullptr, name, typeArgs, refTag) {
  }

std::vector<Type> & TemplatedType::getTypeArgs() {
  return typeArgs;
}

TemplatedType::~TemplatedType() {
}

  void TemplatedType::print(printer::Printer* prt) {
    prt->print(this);
  }
  
  
} /* namespace code */
} /* namespace swift */
