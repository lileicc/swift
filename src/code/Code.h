/*
 * Code.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <vector>
#include "ArraySubscriptExpr.h"
#include "BinaryOperator.h"
#include "BooleanLiteral.h"
#include "BreakStmt.h"
#include "CallExpr.h"
#include "CaseStmt.h"
#include "ClassDecl.h"
#include "CompoundStmt.h"
#include "ContinueStmt.h"
#include "Decl.h"
#include "DeclStmt.h"
#include "DeleteStmt.h"
#include "Expr.h"
#include "FieldDecl.h"
#include "ForStmt.h"
#include "FunctionDecl.h"
#include "FloatingLiteral.h"
#include "IfStmt.h"
#include "IntegerLiteral.h"
#include "NamespaceDecl.h"
#include "NewExpr.h"
#include "ParamVarDecl.h"
#include "Type.h"
#include "ReturnStmt.h"
#include "SpecialStmt.h"
#include "SwitchStmt.h"
#include "Stmt.h"
#include "StringLiteral.h"
#include "VarDecl.h"
#include "VarRef.h"

namespace swift {
namespace printer {
class CPPPrinter;
}
}

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
  void addDecl(Decl* d);
  void addStmt(Stmt* st);

  DeclContext& getDecls();
  CompoundStmt& getStmts();

  // For Printer
  void print(printer::Printer* prt);

private:
  DeclContext decls;
  CompoundStmt stmts;
};

} /* namespace code */
} /* namespace swift */
