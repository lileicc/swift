/*
 * FieldDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <memory>
#include <vector>
#include "VarDecl.h"
#include "ClassDecl.h"
#include "Type.h"

namespace swift {
namespace code {

class FieldDecl: public swift::code::VarDecl {
public:
  FieldDecl(ClassDecl* cd, std::string name, Type ty, Expr* value = nullptr);
  FieldDecl(ClassDecl* cd, std::string name, std::vector<Expr*> arr, Type ty, Expr* value = nullptr);
  ~FieldDecl();

  static FieldDecl* createFieldDecl(ClassDecl* cd, std::string name, Type ty,
      Expr* value = nullptr);

  static FieldDecl* createFieldDecl(ClassDecl* cd, std::string name, std::vector<Expr*> arr,
    Type ty, Expr* value = nullptr);

  // For Printer
  virtual void print(printer::Printer* prt);
};

} /* namespace code */
} /* namespace swift */
