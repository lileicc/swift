/*
 * VarDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "VarDecl.h"

namespace swift {
namespace code {

VarDecl::VarDecl(DeclContext * context, std::string id, Type ty, Expr* value) :
    parent(context), id(id), ty(ty), value(value) {
}

VarDecl::VarDecl(DeclContext * context, std::string id, std::vector<Expr*> arr, Type ty, Expr* value) :
  parent(context), id(id), ty(ty), arr(arr), value(value) {
}

VarDecl::~VarDecl() {
  if (value != NULL)
    delete value;
  for (auto p : arr)
    if (p != NULL)
      delete p;
}

const std::string& VarDecl::getId() const {
  return id;
}

Type& VarDecl::getType() {
  return ty;
}

Expr* VarDecl::getValue() {
  return value;
}

const std::vector<Expr*>& VarDecl::getArrArgs() const {
  return arr;
}

VarDecl* VarDecl::createVarDecl(DeclContext* cd, std::string name, Type ty,
  Expr* value) {
  VarDecl* fd = new VarDecl(cd, name, ty, value);
  cd->addDecl(fd);
  return fd;
}

VarDecl* VarDecl::createVarDecl(DeclContext* cd, std::string name, std::vector<Expr*> arr,
  Type ty, Expr* value) {
  VarDecl* fd = new VarDecl(cd, name, arr, ty, value);
  cd->addDecl(fd);
  return fd;
}

// For Printer
void VarDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
