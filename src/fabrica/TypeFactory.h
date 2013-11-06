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
#include "../ir/InstSymbol.h"
#include "../ir/NameTy.h"
#include "../ir/IRConst.h"

namespace swift {
namespace fabrica {

class TypeFactory {
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
   * get the NameTy associated with the name
   */
  const ir::NameTy* getNameTy(const std::string& name) const;

  /**
   * get the Ty associated with the name
   */
  const ir::Ty* getTy(const std::string& name) const;

  /**
   * add the string symbol for the instance of the type
   * return
   *   false if the symbol is already defined.
   *   true if succeed
   */
  bool addInstSymbol(const ir::NameTy * typ, const std::string& name);

  /**
   * add the attribute for the NameTy (type in blog)
   */
  bool addOriginAttr(const ir::NameTy * srcty, const ir::NameTy* retTy, const std::string& name);

  /**
   * get the instance symbol for a given name
   * return NULL if not found
   */
  const ir::InstSymbol * getInstSymbol(const std::string& name) const;

  /**
   * get the origin attribute
   * return NULL if not found
   */
  const ir::OriginAttr * getOriginAttr(const std::string& name) const;
private:
  std::map<std::string, const ir::Ty*> tyTable; //mapping from name to a declared type
  std::map<std::string, const ir::InstSymbol*> instanceTable; //mapping from name to distinct instance symbol
  std::map<std::string, const ir::OriginAttr*> attrTable; // mapping from origin name(signature) to attribute of type
  static const ir::Ty INT_TY;
  static const ir::Ty BOOL_TY;
  static const ir::Ty DOUBLE_TY;
  static const ir::Ty STRING_TY;
};

}
} /* namespace swift */
