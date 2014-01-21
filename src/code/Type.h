/*
 * Type.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "Expr.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class Type {
public:
  Type(std::string name, bool refTag=false);
  Type(Expr* scope, std::string name, bool refTag=false);
  ~Type();

  const std::string& getName() const;
  bool isRef() const;

  Expr* getScope();

  // For Printer
  void print(printer::Printer* prt);
private:
  std::string name;
  bool refTag;
  Expr* scope;
};

} /* namespace code */
} /* namespace swift */
