/*
 * NumStRef.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "CardinalityExpr.h"

namespace swift {
namespace absyn {

CardinalityExpr::CardinalityExpr(int l, int c, Expr* e) :
    Expr(l, c) {
  args.push_back(e);
}

CardinalityExpr::~CardinalityExpr() {
}

// For Debugging Use
void CardinalityExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(CardinalityExpr:\n", indent, "");
  if (args[0] != NULL)
    args[0]->print(file, indent + 2);
  fprintf(file, "%*s)\n", indent, "");
}

Expr* CardinalityExpr::clone() {
  CardinalityExpr* ret = new CardinalityExpr(*this);
  ret->cloneArgs();
  return ret;
}

}
}
