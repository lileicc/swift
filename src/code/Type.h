/*
 * Type.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <vector>
#include "Expr.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class Type {
public:
  Type(std::string name, bool refTag=false);
  Type(Expr* scope, std::string name, bool refTag=false);
  Type(std::string name, const std::vector<Type> typeArgs, bool refTag=false);
  Type(Expr* scope, std::string name, const std::vector<Type> typeArgs, bool refTag=false);
  Type(const Type baseType, const std::vector<Type> typeArgs, bool refTag=false);
  ~Type();

  const std::string& getName() const;
  bool isRef() const;
  std::vector<Type> & getTypeArgs();

  Expr* getScope();

  // For Printer
  virtual void print(printer::Printer* prt);
private:
  Expr* scope;
  std::string name;
  std::vector<Type> typeArgs;
  bool refTag;
};

} /* namespace code */
} /* namespace swift */
