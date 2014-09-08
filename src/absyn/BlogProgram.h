/*
 * BlogProgram.h
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 *
 *  Note :
 *    This node appears only ONCE in the syntax tree
 *
 */

#pragma once

#include <vector>

#include "Absyn.h"
#include "ArrayExpr.h"
#include "BoolLiteral.h"
#include "CardinalityExpr.h"
#include "CaseExpr.h"
#include "CondSet.h"
#include "Decl.h"
#include "DistinctDecl.h"
#include "DistrExpr.h"
#include "DoubleLiteral.h"
#include "Evidence.h"
#include "Expr.h"
#include "FuncApp.h"
#include "FuncDecl.h"
#include "IfExpr.h"
#include "IntLiteral.h"
#include "Literal.h"
#include "ListSet.h"
#include "MapExpr.h"
#include "NullLiteral.h"
#include "NumStDecl.h"
#include "OpExpr.h"
#include "OriginDecl.h"
#include "QuantExpr.h"
#include "Query.h"
#include "SetExpr.h"
#include "Stmt.h"
#include "StringLiteral.h"
#include "Symbol.h"
#include "TimeStampLiteral.h"
#include "TupleSetExpr.h"
#include "Ty.h"
#include "TypDecl.h"
#include "VarDecl.h"
#include "VarRef.h"

namespace swift {
namespace absyn {

class BlogProgram: public Absyn {
  std::vector<Stmt*> args;
public:
  BlogProgram(int l, int r);
  virtual ~BlogProgram();

  size_t size();
  void add(Stmt* decl);
  Stmt* get(int k);
  const std::vector<Stmt*>& getAll();
  std::vector<Stmt*>& getAllRef();

  // For Debugging Use
  void print(FILE* file, int indent);
};

}
}
