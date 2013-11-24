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
#include "QualType.h"

namespace swift {
namespace code {

class FunctionDecl: public Decl, public DeclContext {
public:
  ~FunctionDecl();

  virtual void addStmt(Stmt* st);
  virtual void setParams(std::vector<ParamVarDecl* > params);
  bool isInline();

  static FunctionDecl* createFunctionDecl(DeclContext * context, std::string name, QualType ty, bool inlineTag=false);
protected:
  FunctionDecl(DeclContext * context, std::string name, QualType ty, bool inlineTag);

private:
  DeclContext* parent;
  std::string name;
  QualType retTy;
  CompoundStmt body;
  bool inlineTag;
  std::vector<ParamVarDecl*> params;
};

} /* namespace code */
} /* namespace swift */
