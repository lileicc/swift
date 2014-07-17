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
  std::vector<Type> typeArgs, bool refTag, bool ptrTag, bool constTag) :
    scope(scope), name(name), typeArgs(typeArgs), refTag(refTag), ptrTag(ptrTag) {
}

Type::Type(std::vector<std::string> scope, std::string name, Type typeArg,
  bool refTag, bool ptrTag, bool constTag) :
    Type(scope, name, std::vector<Type>( { typeArg }), refTag, ptrTag) {
}

Type::Type(const std::string name, bool refTag, bool ptrTag, bool constTag) :
  Type(std::vector<std::string>(), name, std::vector<Type>(), refTag, ptrTag) {
}

Type::Type(std::vector<std::string> scope, std::string name, bool refTag, bool ptrTag, bool constTag) :
  Type(scope, name, std::vector<Type>(), refTag, ptrTag) {
}

bool Type::hasScope() const {
  return scope.size() > 0;
}

Type::Type(std::string name, std::vector<Type> typeArgs, bool refTag, bool ptrTag, bool constTag) :
    Type(std::vector<std::string>(), name, typeArgs, refTag, ptrTag) {
}

Type::Type(Type baseType, std::vector<Type> typeArgs, bool refTag, bool ptrTag, bool constTag) :
    Type(baseType.scope, baseType.name, typeArgs, refTag, ptrTag) {
}

Type::~Type() {
}

const std::string& Type::getName() const {
  return name;
}


void Type::setRef(bool refTag) {
  this->refTag = refTag;
}

bool Type::isRef() const {
  return refTag;
}

void Type::setPtr(bool ptrTag) {
  this->ptrTag = ptrTag;
}

bool Type::isPtr() const {
  return ptrTag;
}

void Type::setConst() {
  this->constTag = true;
}

bool Type::isConst() const {
  return constTag;
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

