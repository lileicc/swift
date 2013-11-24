/*
 * Code.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "Stmt.h"
#include "Decl.h"
#include "ClassDecl.h"
#include "FunctionDecl.h"
#include "FieldDecl.h"
#include "QualType.h"
#include "NamespaceDecl.h"
#include "BinaryOperator.h"
#include "VarRef.h"
#include "IntegerLiteral.h"
#include "ReturnStmt.h"

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
