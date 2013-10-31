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

#include "ArrayExpr.h"
#include "BoolLiteral.h"
#include "CondSet.h"
#include "DistinctDecl.h"
#include "DistrExpr.h"
#include "DoubleLiteral.h"
#include "Evidence.h"
#include "FuncApp.h"
#include "FuncDecl.h"
#include "IfExpr.h"
#include "IntLiteral.h"
#include "ListSet.h"
#include "MapExpr.h"
#include "NullLiteral.h"
#include "NumStDecl.h"
#include "NumStRef.h"
#include "OpExpr.h"
#include "OriginDecl.h"
#include "QuantExpr.h"
#include "Query.h"
#include "StringLiteral.h"
#include "Symbol.h"
#include "TimeStampLiteral.h"
#include "TypDecl.h"
#include "VarDecl.h"
#include "VarRef.h"

namespace swift {

class BlogProgram :
  public swift::Absyn
{
  std::vector<Stmt*> args;
public:
  BlogProgram(int l, int r);
  virtual ~BlogProgram();

  size_t size();
  void add(Stmt* decl);
  Stmt* get(int k);

  // For Debugging Use
  void print(FILE* file, int indent);
};

}