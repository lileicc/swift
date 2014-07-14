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
    SetExpr(l, c), vardecls(vardecls) {
    for(size_t i = 0; i < exps.size(); i++){
      args.push_back(exps[i]);
    }
    args.push_back(cond);
}

TupleSetExpr::~TupleSetExpr() {
}

Expr* TupleSetExpr::getExp(size_t i){
  if (i < args.size()-1) return args[i];
  return NULL;
}

std::vector<VarDecl> TupleSetExpr::getVarDecls(){
  return vardecls;
}

Expr* TupleSetExpr::getCond(){
  return args[args.size() - 1];
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
