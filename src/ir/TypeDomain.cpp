/*
 * TypeDomain.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: yiwu
 */
#include "TypeDomain.h"
namespace swift {
namespace ir {

TypeDomain::TypeDomain(const std::string& name)
  :name(name) {
}

TypeDomain::~TypeDomain()  {
}

const std::string& TypeDomain::getName() {
  return name;
}

void TypeDomain::addRefer(NameTy* ref) {
  refer = ref;
}

NameTy* TypeDomain::getRefer() {
  return refer;
}

void TypeDomain::setPreLen(int l) {
  prelen = l;
}

int TypeDomain::getPreLen() {
  return prelen;
}

void TypeDomain::addNumberStmt(NumberStmt* num) {
  gen.push_back(num);
}

const std::vector<NumberStmt*>& TypeDomain::getAllNumberStmt() {
  return gen;
}

NumberStmt* TypeDomain::getNumberStmt(int k) {
  return gen[k];
}

size_t TypeDomain::getNumberStmtSize() {
  return gen.size();
}

void TypeDomain::addOrigin(OriginAttr* o) {
  originID[o->getName()] = origin.size();
  o->setID(origin.size());
  origin.push_back(o);
}

const std::vector<OriginAttr*>& TypeDomain::getAllOrigin() {
  return origin;
}

OriginAttr* TypeDomain::getOrigin(int k) {
  return origin[k];
}

size_t TypeDomain::getOriginSize() {
  return origin.size();
}

int TypeDomain::getOriginID(const std::string& str) {
  if (originID.find(str) == originID.end()) return -1;
  return originID[str];
}

OriginAttr* TypeDomain::getOrigin(const std::string& str) {
  int id = getOriginID(str);
  if (id < 0) return NULL;
  return origin[id];
}
}
}
