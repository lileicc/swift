/*
 * Query.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "Query.h"

namespace swift {
namespace absyn {

Query::Query(int l, int c, Expr* expr) :
    Stmt(l, c), expr(expr) {
}

Query::~Query() {
  if (expr != NULL)
    delete expr;
}

Expr*& Query::getExpr() {
  return expr;
}

// For Debugging Use
void Query::print(FILE* file, int indent) {
  fprintf(file, "%*s(Query:\n", indent, "");
  if (expr != NULL) {
    fprintf(file, "%*s:expr\n", indent + 2, "");
    expr->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
