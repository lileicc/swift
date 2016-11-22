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
    Stmt(l, c), expr(expr), cond(NULL) {
}

Query::Query(int l, int c, Expr* expr, std::vector<VarDecl> vars) :
    Stmt(l, c), expr(expr), vardecls(vars), cond(NULL) {
}

Query::Query(int l, int c, Expr* expr, std::vector<VarDecl> vars, Expr* cd) :
    Stmt(l, c), expr(expr), vardecls(vars), cond(cd) {
}

Query::~Query() {
  if (expr != NULL)
    delete expr;
  if (cond != NULL)
    delete cond;
}

Expr*& Query::getExpr() {
  return expr;
}

Expr* Query::getCond() {
  return cond;
}

void Query::setCond(Expr* e) {
  cond = e;
}

const VarDecl& Query::getVarDecl(size_t i) const {
  return vardecls[i];
}

const std::vector<VarDecl>& Query::getVarDecls() const {
  return vardecls;
}

void Query::clear() {
  expr = NULL;
  cond = NULL;
  vardecls.clear();
}

// For Debugging Use
void Query::print(FILE* file, int indent) {
  fprintf(file, "%*s(Query:\n", indent, "");
  if (expr != NULL) {
    fprintf(file, "%*s:expr\n", indent + 2, "");
    expr->print(file, indent + 4);
  }
  if (vardecls.size() > 0) {
    fprintf(file, "%*s:enumVars\n", indent+2, "");
    for(size_t i = 0; i < vardecls.size(); i++){
      vardecls[i].print(file, indent+4);
    }
  }
  if (cond != NULL) {
    fprintf(file, "%*s:cond\n", indent+2, "");
    cond->print(file, indent+4);
  }

  fprintf(file, "%*s)\n", indent, "");
}

}
}
