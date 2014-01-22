/*
 * TemplatedType.h
 *
 *  Created on: Jan 21, 2014
 *      Author: leili
 */

#pragma once
#include <vector>
#include <string>
#include "Type.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class TemplatedType: public swift::code::Type {
public:
  TemplatedType(std::string name, std::vector<Type> typeArgs, bool refTag=false);
  TemplatedType(Expr* scope, std::string name, std::vector<Type> typeArg, bool refTag=false);
  virtual ~TemplatedType();
  
  std::vector<Type> & getTypeArgs();
  
  // For Printer
  void print(printer::Printer* prt);
  
private:
  std::vector<Type> typeArgs;
};

} /* namespace code */
} /* namespace swift */
