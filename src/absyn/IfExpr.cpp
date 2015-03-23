/*
 * IfExpr.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#include "IfExpr.h"

namespace swift {
namespace absyn {

IfExpr::IfExpr(int l, int r, Expr* cond, Expr* then_clause, Expr* else_clause) :
    Expr(l, r) {
  args.push_back(cond);
  args.push_back(then_clause);
  args.push_back(else_clause);
}

IfExpr::~IfExpr() {
}

Expr* IfExpr::getCond() {
  return args[0];
}

Expr* IfExpr::getThen() {
  return args[1];
}

Expr* IfExpr::getElse() {
  return args[2];
}

// For Debugging Use
void IfExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(IfExpr:\n", indent, "");
  if (getCond() != NULL) {
    fprintf(file, "%*s:cond\n", indent + 2, "");
    getCond()->print(file, indent + 4);
  }
  if (getThen() != NULL) {
    fprintf(file, "%*s:then\n", indent + 2, "");
    getThen()->print(file, indent + 4);
  }
  if (getElse() != NULL) {
    fprintf(file, "%*s:else\n", indent + 2, "");
    getElse()->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

std::string IfExpr::toString() {
  std::string ret = "if (";
  if (getCond() != NULL)
    ret += getCond()->toString();
  ret += ") then ";
  if (getThen() != NULL)
    ret += getThen()->toString();
  if (getElse() != NULL) {
    ret += " else " + getElse()->toString();
  }
  return ret;
}

Expr* IfExpr::clone() {
  IfExpr* ret = new IfExpr(*this);
  ret->cloneArgs();
  return ret;

}

}
} /* namespace swift */
