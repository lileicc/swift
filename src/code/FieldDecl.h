/*
 * FieldDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <memory>
#include "Decl.h"
#include "ClassDecl.h"
#include "Type.h"

namespace swift {
namespace code {

class FieldDecl: public swift::code::Decl {
public:
  FieldDecl(ClassDecl* cd, std::string name, Type ty);
  ~FieldDecl();

  static FieldDecl* createFieldDecl(ClassDecl* cd, std::string name, Type ty);

  const std::string& getId() const ;
  Type& getType();

  // For Printer
  void print(printer::Printer* prt);

private:
  ClassDecl* parent;
  std::string id;
  Type ty;
};

} /* namespace code */
} /* namespace swift */
