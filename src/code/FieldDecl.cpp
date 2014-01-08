/*
 * FieldDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "FieldDecl.h"
#include "Type.h"

namespace swift {
namespace code {

FieldDecl::FieldDecl(ClassDecl* cd, std::string name,
   Type ty) : parent(cd), id(name), ty(ty) {
}

FieldDecl::~FieldDecl() {
}

FieldDecl* FieldDecl::createFieldDecl(ClassDecl* cd, std::string name,
    Type ty) {
  FieldDecl* fd = new FieldDecl(cd, name, ty);
  cd->addDecl(fd);
  return fd;
}

const std::string& FieldDecl::getId() const {
  return id;
}

Type& FieldDecl::getType() {
  return ty;
}

// For Printer
void FieldDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
