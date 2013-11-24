/*
 * FunctionDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "FunctionDecl.h"

namespace swift {
namespace code {

FunctionDecl* FunctionDecl::createFunctionDecl(DeclContext* context,
    std::string name, QualType ty, bool inlineTag) {
  FunctionDecl* fd = new FunctionDecl(context, name, ty, inlineTag);
  context->addDecl(fd);
  return fd;
}

FunctionDecl::FunctionDecl(DeclContext * context, std::string name, QualType ty,
    bool inlineTag) :
    parent(context), name(name), retTy(ty), inlineTag(inlineTag) {
}

FunctionDecl::~FunctionDecl() {
}

void swift::code::FunctionDecl::addStmt(Stmt* st) {
  body.addStmt(st);
}

void FunctionDecl::setParams(std::vector<ParamVarDecl*> params) {
  this->params = params;
}

bool swift::code::FunctionDecl::isInline() {
  return inlineTag;
}

} /* namespace code */
} /* namespace swift */
