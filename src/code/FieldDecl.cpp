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
   Type ty, Expr* value) : VarDecl(cd, name, ty, value) {
}

FieldDecl::~FieldDecl() {
}

FieldDecl* FieldDecl::createFieldDecl(ClassDecl* cd, std::string name,
    Type ty, Expr* value) {
  FieldDecl* fd = new FieldDecl(cd, name, ty, value);
  cd->addDecl(fd);
  return fd;
}

// For Printer
void FieldDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
