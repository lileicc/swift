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
      args.push_back(exps[i]);
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
  fprintf(file, "%*s(VarDecls:\n", indent+2, "");
  for(size_t i = 0; i < vardecls.size(); i++){
    vardecls[i].print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent+2, "");

  fprintf(file, "%*s(Exps:\n", indent+2, "");
  for(size_t i = 0; i < args.size() - 1; i++){
    if (args[i] != NULL){
      args[i]->print(file, indent+4);
    }
  }
  fprintf(file, "%*s)\n", indent+2, "");

  fprintf(file, "%*s:cond\n", indent+2, "");
  if (args[args.size()-1] != NULL){
    args[args.size()-1]->print(file, indent+4);
  }

  fprintf(file, "%*s)\n", indent, "");
}

}
}
