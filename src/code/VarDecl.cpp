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

VarDecl::~VarDecl() {
}

const std::string& VarDecl::getId() const {
  return id;
}

// For Printer
void VarDecl::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
