/*
 * FunctionDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include <memory>
#include "Decl.h"
#include "DeclContext.h"
#include "Stmt.h"
#include "CompoundStmt.h"

namespace swift {
namespace code {

class FunctionDecl: public Decl, public DeclContext {
public:
  FunctionDecl();
  ~FunctionDecl();
  virtual void addStmt(Stmt* st);
private:
  CompoundStmt body;
};

} /* namespace code */
} /* namespace swift */
