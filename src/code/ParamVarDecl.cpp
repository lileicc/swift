/*
 * ParamVarDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ParamVarDecl.h"

namespace swift {
namespace code {

ParamVarDecl::ParamVarDecl(DeclContext * context, std::string id, Type ty, Expr* value) :
    VarDecl(context, id, ty, value) {
}

ParamVarDecl::~ParamVarDecl() {
}

// For Printer
void ParamVarDecl::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
