/*
 * OpExpr.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: leili
 */

#include "OpExpr.h"

namespace swift {
namespace absyn {

OpExpr::OpExpr(int l, int c, AbsynConstant op, Expr* left, Expr* right) :
    Expr(l, c), op(op) {
  args.push_back(left);
  args.push_back(right);
}

OpExpr::~OpExpr() {
}

AbsynConstant OpExpr::getOp() {
  return op;
}

Expr* OpExpr::getLeft() {
  return args[0];
}

Expr* OpExpr::getRight() {
  return args[1];
}

// For Debugging Use
void OpExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(OpExpr:\n", indent, "");
  fprintf(file, "%*s:op %d\n", indent + 2, "", op);
  if (args[0] != NULL) {
    fprintf(file, "%*s:left\n", indent + 2, "");
    args[0]->print(file, indent + 4);
  }
  if (args[1] != NULL) {
    fprintf(file, "%*s:right\n", indent + 2, "");
    args[1]->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

std::string OpExpr::toString() {
  std::string opr = "?";
  switch (op) {
  case AbsynConstant::PLUS: opr = "+"; break;
  case AbsynConstant::MINUS: opr = "-"; break;
  case AbsynConstant::MUL: opr = "*"; break;
  case AbsynConstant::DIV: opr = "/"; break;
  case AbsynConstant::POWER: opr = "^"; break;
  case AbsynConstant::MOD: opr = "%"; break;
  case AbsynConstant::EQ: opr = "="; break;
  case AbsynConstant::NEQ: opr = "!="; break;
  case AbsynConstant::LT: opr = "<"; break;
  case AbsynConstant::GT: opr = ">"; break;
  case AbsynConstant::LE: opr = "<="; break;
  case AbsynConstant::GE: opr = ">="; break;
  case AbsynConstant::AND: opr = "&"; break;
  case AbsynConstant::OR: opr = "|"; break;
  case AbsynConstant::NOT: opr = "!"; break;
  case AbsynConstant::IMPLY: opr = "->"; break;
  case AbsynConstant::SUB: opr = "["; break;
  case AbsynConstant::AT: opr = "@"; break;
  default: opr = "?"; break;
  }
  std::string ret;
  if (getLeft() != NULL) ret += getLeft()->toString();
  ret += opr;
  if (getRight() != NULL) ret += getRight()->toString();
  if (opr == "[") ret += "]";
  return ret;
}

Expr* OpExpr::clone() {
  OpExpr* ret = new OpExpr(*this);
  ret->cloneArgs();
  return ret;
}

}
} /* namespace swift */
