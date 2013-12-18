/*
 * VarDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <cstdlib>
#include <string>
#include "Decl.h"
#include "Type.h"
#include "DeclContext.h"
#include "Expr.h"

namespace swift {
namespace code {

class VarDecl: public swift::code::Decl {
public:
  VarDecl(DeclContext * context, std::string id, Type ty, Expr* value=NULL);
  virtual ~VarDecl();

  const std::string& getId() const;
  Type& getType();
  Expr* getValue();

  // For Printer
  void print(printer::CPPPrinter* prt);
protected:
  DeclContext* parent;
  std::string id;
  Type ty;
  Expr* value; // initial value
};

} /* namespace code */
} /* namespace swift */
