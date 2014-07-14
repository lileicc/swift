/*
 * CaseExpr.cpp
 *
 *  Created on: July 12, 2014
 *      Author: tejas
 */

#include "CaseExpr.h"

namespace swift {
namespace absyn {

CaseExpr::CaseExpr(int l, int c, Expr* test, MapExpr* map) :
    Expr(l, c) {
      args.push_back(test);
      args.push_back((Expr*)map);
}

CaseExpr::~CaseExpr() {
}

Expr* CaseExpr::getTest(){
  return args[0];
}

MapExpr* CaseExpr::getMap(){
  return (MapExpr*)args[1];
}

// For Debugging Use
void CaseExpr::print(FILE* file, int indent) {
  fprintf(file, "%*s(CaseExpr:\n", indent, "");
  if (getTest() != NULL){
    fprintf(file, "%*s:test\n", indent+2, "");
    getTest()->print(file, indent+4);
  }
  if (getMap() != NULL){
    fprintf(file, "%*s:map\n", indent+2, "");
    getMap()->print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
