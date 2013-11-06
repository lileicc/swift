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
#include "../ir/FuncDefn.h"

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
  bool addFuncDefn(const std::string& name, const ir::Ty* retTy,
      std::vector<const ir::VarDecl*> args, bool isRand);

  /**
   * look up the table to find the function with the same signature
   * return NULL if not found
   */
  ir::FuncDefn* getFunc(const std::string& name,
      const std::vector<const ir::VarDecl*> args);
private:
  std::map<std::string, ir::FuncDefn*> funTable;
};

} /* namespace fabrica */
} /* namespace swift */
