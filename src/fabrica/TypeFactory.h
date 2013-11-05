/*
 * TypeFactory.h
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <map>
#include "../ir/Ty.h"
#include "../ir/TypeDomain.h"
#include "../ir/NameTy.h"

namespace swift {
namespace fabrica{

class TypeFactory{
public:
  TypeFactory();
  ~TypeFactory();
  bool addNameTy(const std::string& str);
private:
  std::map<std::string, ir::Ty*> tyTable;
};

}
} /* namespace swift */
