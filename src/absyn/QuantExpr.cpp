/*
 * QunatExpr.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "QuantExpr.h"

namespace swift {
namespace absyn {

QuantExpr::QuantExpr(int l, int c, AbsynConstant typ, VarDecl var, Expr* cond) :
    Expr(l, c), typ(typ), var(var) {
  add(cond);
}

QuantExpr::~QuantExpr() {
}

AbsynConstant QuantExpr::getTyp() {
  return typ;
}

const VarDecl& QuantExpr::getVar() {
  return var;
}

Expr* QuantExpr::getCond() {
  return args[0];
}

// For Debugging Use
void QuantExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(QuantExpr:\n", indent, "");
  fprintf(file, "%*s:typ %d\n", indent + 2, "", typ);
  var.print(file, indent + 2);
  if (args[0] != NULL) {
    fprintf(file, "%*s:cond\n", indent + 2, "");
    args[0]->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

std::string QuantExpr::toString() {
  std::string ret = (typ == AbsynConstant::FORALL ? "forall " : "exists ") + var.toString();
  if (args[0] != NULL) {
    ret += ": " + args[0]->toString();
  }
  return ret;
}

Expr* QuantExpr::clone() {
  QuantExpr* ret = new QuantExpr(*this);
  ret->cloneArgs();
  return ret;
}

}
}
