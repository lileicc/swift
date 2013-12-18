/*
 * FunctionDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include "Decl.h"
#include "DeclContext.h"
#include "Stmt.h"
#include "CompoundStmt.h"
#include "ParamVarDecl.h"
#include "Type.h"

namespace swift {
namespace code {

class FunctionDecl: public Decl, public DeclContext {
public:
  virtual ~FunctionDecl();

  virtual void addStmt(Stmt* st);
  virtual void setParams(std::vector<ParamVarDecl* > params);
  virtual std::vector<ParamVarDecl*>& getParams();
  bool isInline();
  Type& getType();
  CompoundStmt& getBody();
  const std::string& getName() const;
  static FunctionDecl* createFunctionDecl(DeclContext * context, std::string name, Type ty, bool inlineTag=false);

  // For Printer
  virtual void print(printer::CPPPrinter* prt);
protected:
  FunctionDecl(DeclContext * context, std::string name, Type ty, bool inlineTag);

private:
  DeclContext* parent;
  std::string name;
  Type retTy;
  CompoundStmt body;
  bool inlineTag;
  std::vector<ParamVarDecl*> params;
};

} /* namespace code */
} /* namespace swift */
