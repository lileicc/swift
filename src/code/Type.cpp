/*
 * Type.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Type.h"

namespace swift {
namespace code {
Type::Type(std::vector<std::string> scope, std::string name,
    std::vector<Type> typeArgs, bool refTag) :
    scope(scope), name(name), typeArgs(typeArgs), refTag(refTag) {
}

Type::Type(std::vector<std::string> scope, std::string name, Type typeArg,
    bool refTag) :
    Type(scope, name, std::vector<Type>( { typeArg }), refTag) {
}

Type::Type(const std::string name, bool refTag) :
    Type(std::vector<std::string>(), name, std::vector<Type>(), refTag) {
}

Type::Type(std::vector<std::string> scope, std::string name, bool refTag) :
    Type(scope, name, std::vector<Type>(), refTag) {
}

bool Type::hasScope() const {
  return scope.size() > 0;
}

Type::Type(std::string name, std::vector<Type> typeArgs, bool refTag) :
    Type(std::vector<std::string>(), name, typeArgs, refTag) {
}

Type::Type(Type baseType, std::vector<Type> typeArgs, bool refTag) :
    Type(baseType.scope, baseType.name, typeArgs, refTag) {
}

Type::~Type() {
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

std::vector<std::string>& Type::getScope() {
  return scope;
}

// For Printer
void Type::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

