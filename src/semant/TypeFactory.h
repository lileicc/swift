/*
 * TypeFactory.h
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <map>
#include "../ir/IRHeader.h"

namespace swift {
namespace semant{

class TypeFactory {
public:
  TypeFactory();
  ~TypeFactory();
  bool addNameTy(const std::string& str);
private:
  std::map<std::string, ir::Ty*> tyTable;
};

}
} /* namespace swift */