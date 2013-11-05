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
  /**
   * add a new BLOG type into the table
   * returns:
   *    true if the success,
   *    false if the type is already declared.
   */
  bool addNameTy(const std::string& name);

  /**
   * get the NameTy associated with the name <str>
   */
  ir::NameTy* getNameTy(const std::string& name);

  /**
   * add the string symbol for the instance of the type
   * return
   *   false if the symbol is already defined.
   *   true if succeed
   */
  bool addInstSymbol(ir::NameTy* typ, const std::string& name);

  /**
   * get the instance symbol for a given name
   * return NULL if not found
   */
  ir::InstSymbol* getInstSymbol(const std::string& name);
private:
  std::map<std::string, ir::Ty*> tyTable;
  std::map<std::string, ir::InstSymbol*> instanceTable;
};

}
} /* namespace swift */
