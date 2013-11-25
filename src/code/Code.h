/*
 * Code.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "ArraySubscriptExpr.h"
#include "BinaryOperator.h"
#include "BreakStmt.h"
#include "CaseStmt.h"
#include "ClassDecl.h"
#include "CompoundStmt.h"
#include "Decl.h"
#include "DeclStmt.h"
#include "Expr.h"
#include "FieldDecl.h"
#include "ForStmt.h"
#include "FunctionDecl.h"
#include "FloatingLiteral.h"
#include "IfStmt.h"
#include "IntegerLiteral.h"
#include "NamespaceDecl.h"
#include "ParamVarDecl.h"
#include "QualType.h"
#include "ReturnStmt.h"
#include "SwitchStmt.h"
#include "Stmt.h"
#include "VarDecl.h"
#include "VarRef.h"

namespace swift {
namespace code {
class Decl;
class Stmt;
} /* namespace code */
} /* namespace swift */

namespace swift {
namespace code {

class Code {
public:
  Code();
  ~Code();
  void addDecl(Decl d);
  void addStmt(Stmt st);
};

} /* namespace code */
} /* namespace swift */
