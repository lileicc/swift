/*
 * LambdaExpr.h
 *
 *  Created on: Feb 11, 2014
 *      Author: yiwu
 */

/*
 * Lambda Expression
 *  Basic Structure:
 *     [LambdaKind] (ParamVarDecl) -> Type {CompoundStmt}
 *  Note: Type can be Empty (then [-> Type] part will be ignored)
 */

#pragma once
#include <vector>
#include <string>
#include "Expr.h"
#include "CompoundStmt.h"
#include "Type.h"
#include "ParamVarDecl.h"

namespace swift {
namespace code {

enum class LambdaKind {
  NONE, // No Variable Capture: []
  REF, // Reference of Variable Capture: [&]
  COPY, // Copy of Variable Capture: [=]
  THIS, // Capture this pointer: [this]
  NA // Other
};

class LambdaExpr: public Expr {
public:
  LambdaExpr(LambdaKind kind = LambdaKind::REF, Type ty = Type(""));
  ~LambdaExpr();

  const LambdaKind& getKind() const;
  void addStmt(Stmt* stmt);
  void setBody(CompoundStmt cpd);
  CompoundStmt& getBody();
  void setType(Type ty);
  Type& getType();
  void addParam(ParamVarDecl* param);
  void setParams(std::vector<ParamVarDecl*> params);
  std::vector<ParamVarDecl*>& getParams();

  void clear();

  // For Printer
  void print(printer::Printer* prt);
private:
  LambdaKind kind;
  Type retType;
  std::vector<ParamVarDecl*> params;
  CompoundStmt body;
};

} /* namespace code */
} /* namespace swift */
