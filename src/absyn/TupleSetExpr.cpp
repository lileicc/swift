/*
 * TupleSetExpr.cpp
 *
 *  Created on: July 12, 2014
 *      Author: tejas
 */

#include "TupleSetExpr.h"

namespace swift {
namespace absyn {

TupleSetExpr::TupleSetExpr(int l, int c, std::vector<Expr*> exps, 
                            std::vector<VarDecl> vardecls, Expr* cond) :
    SetExpr(l, c), vardecls(vardecls), cond(cond) {
    for(size_t i = 0; i < exps.size(); i++){
      add(exps[i]);
    }
}

TupleSetExpr::~TupleSetExpr() {
  if (cond != NULL)
    delete cond;
}

Expr* TupleSetExpr::getExp(size_t i) const {
  if (i < args.size()) return args[i];
  return NULL;
}

const std::vector<Expr*>& TupleSetExpr::getExps() const {
  return args;
}

const VarDecl& TupleSetExpr::getVarDecl(size_t i) const {
  return vardecls[i];
}

const std::vector<VarDecl>& TupleSetExpr::getVarDecls() const {
  return vardecls;
}

Expr* TupleSetExpr::getCond() const {
  return cond;
}

// For Debugging Use
void TupleSetExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(TupleSetExpr:\n", indent, "");

  fprintf(file, "%*s:setTuple\n", indent+2, "");
  for(size_t i = 0; i < args.size(); i++){
    if (args[i] != NULL){
      args[i]->print(file, indent+4);
    }
  }

  fprintf(file, "%*s:cond\n", indent+2, "");
  if (cond != NULL){
    cond->print(file, indent+4);
  }

  fprintf(file, "%*s:enumVars\n", indent+2, "");
  for(size_t i = 0; i < vardecls.size(); i++){
    vardecls[i].print(file, indent+4);
  }

  fprintf(file, "%*s)\n", indent, "");
}

std::string TupleSetExpr::toString() {
  std::string ret = "{";
  for (size_t i = 0; i < args.size(); ++i) {
    if (i > 0) ret += ", ";
    if (args[i] != NULL) ret += args[i]->toString();
  }
  ret += " for ";
  for (size_t i = 0; i < vardecls.size(); ++i) {
    if (i > 0) ret += ", ";
    ret += vardecls[i].toString();
  }
  if (cond != NULL) {
    ret += ": " + cond->toString();
  }
  return ret + "}";
}

void TupleSetExpr::cloneArgs() {
  for (size_t i = 0; i < args.size(); ++ i)
    if (args[i] != NULL)
      args[i] = args[i]->clone();
  if (cond != NULL)
    cond = cond->clone();
}

Expr* TupleSetExpr::clone() {
  TupleSetExpr* ret = new TupleSetExpr(*this);
  ret->cloneArgs();
  return ret;
}

}
}
