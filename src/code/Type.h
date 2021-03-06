/*
 * Type.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Expr.h"
#include "../printer/Printer.h"

namespace swift {
namespace code {

class Type {
public:
  Type(std::string name, bool refTag = false, bool ptrTag = false, bool constTag = false);
  Type(std::vector<std::string> scope, std::string name, bool refTag = false, bool ptrTag = false, bool constTag = false);
  Type(std::string name, std::vector<Type> typeArgs, bool refTag = false, bool ptrTag = false, bool constTag = false);
  Type(std::vector<std::string> scope, std::string name,
    std::vector<Type> typeArgs, bool refTag = false, bool ptrTag = false, bool constTag = false);
  Type(std::vector<std::string> scope, std::string name, Type typeArg,
    bool refTag = false, bool ptrTag = false, bool constTag = false);
  Type(Type baseType, std::vector<Type> typeArgs, bool refTag = false, bool ptrTag = false, bool constTag = false);
  ~Type();

  const std::string& getName() const;
  void setRef(bool refTag = false);
  bool isRef() const;
  void setPtr(bool ptrTag = false);
  bool isPtr() const;
  void setConst(bool consTag = false);
  bool isConst() const;
  bool hasScope() const;
  std::vector<Type> & getTypeArgs();

  std::vector<std::string>& getScope();
  
  friend bool operator ==(const Type& a, const Type& b) {
    if (a.name != b.name) return false;
    if (a.scope.size() != b.scope.size()) return false;
    if (a.typeArgs.size() != b.typeArgs.size()) return false;
    if (a.refTag != b.refTag) return false;
    if (a.ptrTag != b.ptrTag) return false;
    if (a.constTag != b.constTag) return false;
    if ((! a.scope.empty()) && (!std::equal(a.scope.begin(), a.scope.end(), b.scope.begin()))) return false;
    if ((! a.typeArgs.empty()) && (!std::equal(a.typeArgs.begin(), a.typeArgs.end(), b.typeArgs.begin()))) return false;
    return true;
  };
  
  friend bool operator !=(const Type& a, const Type& b) {
    return !(a == b);
  }

  // For Printer
  virtual void print(printer::Printer* prt);
private:
  std::vector<std::string> scope;
  std::string name;
  std::vector<Type> typeArgs;
  bool refTag;
  bool ptrTag;
  bool constTag;
};

} /* namespace code */
} /* namespace swift */
