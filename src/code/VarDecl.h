/*
 * VarDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include "Decl.h"
#include "Type.h"
#include "DeclContext.h"
#include "Expr.h"

namespace swift {
namespace code {

class VarDecl: public swift::code::Decl {
public:
  VarDecl(DeclContext * context, std::string id, Type ty,
      Expr* value = nullptr);
  VarDecl(DeclContext * context, std::string id, std::vector<Expr*> arr, 
    Type ty, Expr* value = nullptr);
  virtual ~VarDecl();

  const std::string& getId() const;
  Type& getType();
  Expr* getValue();
  const std::vector<Expr*>& getArrArgs() const;

  static VarDecl* createVarDecl(DeclContext* cd, std::string name, Type ty,
    Expr* value = nullptr);

  static VarDecl* createVarDecl(DeclContext* cd, std::string name, std::vector<Expr*> arr,
    Type ty, Expr* value = nullptr);

  // For Printer
  virtual void print(printer::Printer* prt);
protected:
  DeclContext* parent;
  std::string id;
  Type ty;
  Expr* value; // initial value
  std::vector<Expr*> arr; // for Array Variable Decl
};

} /* namespace code */
} /* namespace swift */
