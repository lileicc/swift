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
  Type(std::string name, bool refTag = false);
  Type(std::vector<std::string> scope, std::string name, bool refTag = false);
  Type(std::string name, std::vector<Type> typeArgs, bool refTag = false);
  Type(std::vector<std::string> scope, std::string name,
      std::vector<Type> typeArgs, bool refTag = false);
  Type(std::vector<std::string> scope, std::string name, Type typeArg,
      bool refTag = false);
  Type(Type baseType, std::vector<Type> typeArgs, bool refTag = false);
  ~Type();

  const std::string& getName() const;
  bool isRef() const;
  bool hasScope() const;
  std::vector<Type> & getTypeArgs();

  std::vector<std::string>& getScope();

  // For Printer
  virtual void print(printer::Printer* prt);
private:
  std::vector<std::string> scope;
  std::string name;
  std::vector<Type> typeArgs;
  bool refTag;
};

} /* namespace code */
} /* namespace swift */
