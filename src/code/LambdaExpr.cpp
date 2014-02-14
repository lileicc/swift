/*
 * LambdaExpr.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: yiwu
 */

#include "LambdaExpr.h"

namespace swift {
namespace code {

LambdaExpr::LambdaExpr(LambdaKind kind, Type ty) :
    kind(kind), retType(ty) {
}

LambdaExpr::~LambdaExpr() {
  for (auto p : params)
    if (p != NULL) delete p;
}

const LambdaKind& LambdaExpr::getKind() const {
  return kind;
}

void LambdaExpr::addStmt(Stmt* stmt) {
  body.addStmt(stmt);
}


CompoundStmt& LambdaExpr::getBody() {
  return body;
}

void LambdaExpr::setType(Type ty) {
  retType = ty;
}

Type& LambdaExpr::getType() {
  return retType;
}

void LambdaExpr::addParam(ParamVarDecl* param) {
  params.push_back(param);
}

std::vector<ParamVarDecl*>& LambdaExpr::getParams() {
  return params;
}

// For Printer
void LambdaExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

