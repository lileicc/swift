/*
 * Functory.h
 *
 *  Created on: Nov 5, 2013
 *      Author: leili
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include "../ir/Ty.h"
#include "../ir/VarDecl.h"

namespace swift {
namespace fabrica {

/**
 * a class for creating all functions for intermediate representation
 */
class Functory {
public:
  Functory();
  ~Functory();

  /**
   * add a function with name, return type, and a list of arguments
   */
  bool addFuncDefn(const std::string& name, ir::Ty* retTy, const std::vector<ir::VarDecl*>& args);
private:
  std::map<std::string, ir::FuncDefn*> funTable;
};

} /* namespace fabrica */
} /* namespace swift */
