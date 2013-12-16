/*
 * ParamVarDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ParamVarDecl.h"

namespace swift {
namespace code {

ParamVarDecl::ParamVarDecl(DeclContext * context, std::string id, Type ty) :
    VarDecl(context, id, ty) {
}

ParamVarDecl::~ParamVarDecl() {
}

// For Printer
void ParamVarDecl::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
