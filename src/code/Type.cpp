/*
 * Type.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Type.h"

namespace swift {
namespace code {
Type::Type(Expr* scope, std::string name, const std::vector<Type> typeArgs,
    bool refTag) :
    scope(scope), name(name), typeArgs(typeArgs), refTag(refTag) {
}

Type::Type(const std::string name, bool refTag) :
    Type(nullptr, name, std::vector<Type>(), refTag) {
}

Type::Type(Expr* scope, std::string name, bool refTag) :
    Type(scope, name, std::vector<Type>(), refTag) {
}

Type::Type(std::string name, const std::vector<Type> typeArgs, bool refTag) :
    Type(nullptr, name, typeArgs, refTag) {
}
  
Type::Type(const Type baseType, const std::vector<Type> typeArgs, bool refTag) : Type(baseType.scope, baseType.name, typeArgs, refTag) {    
}


Type::~Type() {
  delete scope;
}

const std::string& Type::getName() const {
  return name;
}

bool Type::isRef() const {
  return refTag;
}

std::vector<Type> & Type::getTypeArgs() {
  return typeArgs;
}

Expr* Type::getScope() {
  return scope;
}

// For Printer
void Type::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

