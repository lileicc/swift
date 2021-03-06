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
#include "ClassConstructor.h"
#include "CallClassConstructor.h"
#include "ClassDecl.h"
#include "CompoundStmt.h"
#include "ContinueStmt.h"
#include "Decl.h"
#include "DeclContext.h"
#include "DeclStmt.h"
#include "Expr.h"
#include "FieldDecl.h"
#include "ForStmt.h"
#include "FunctionDecl.h"
#include "FloatingLiteral.h"
#include "IfStmt.h"
#include "IntegerLiteral.h"
#include "LambdaExpr.h"
#include "ListInitExpr.h"
#include "NamespaceDecl.h"
#include "NewExpr.h"
#include "NullLiteral.h"
#include "ParamVarDecl.h"
#include "Type.h"
#include "ReturnStmt.h"
#include "SpecialMacro.h"
#include "SwitchStmt.h"
#include "Stmt.h"
#include "StringLiteral.h"
#include "TemplateExpr.h"
#include "VarDecl.h"
#include "Identifier.h"

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

class Code: public code::DeclContext {
public:
  Code();
  ~Code();

  void addMacro(SpecialMacro* macro);
  std::vector<SpecialMacro*> & getAllMacros();

  void addOption(std::string op);
  const std::vector<std::string>& getAllOptions();

  // For Printer
  void print(printer::Printer* prt);
private:
  std::vector<SpecialMacro*> macros;
  std::vector<std::string> options;
};

} /* namespace code */
} /* namespace swift */
