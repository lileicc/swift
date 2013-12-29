/*
 * Functory.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: leili
 */

#include "Functory.h"

namespace swift {
namespace fabrica {

Functory::Functory() {
  // TODO Auto-generated constructor stub

}

Functory::~Functory() {
  // TODO Auto-generated destructor stub
  // Note: We DO NOT Need to delete all the pointers to FuncDefn here!
}

bool Functory::addFuncDefn(const std::string& name, const ir::Ty * retTy,
    std::vector<std::shared_ptr<ir::VarDecl> > args, bool isRand) {
  if (getFunc(name, args) != NULL) return false;
  // TODO
  // DEBUG: function signature not well designed!!
  //   Note: no arguments is passed to fd!
  //         toSignature() should not include variable name!
  ir::FuncDefn* fd = new ir::FuncDefn(isRand, std::string(name), retTy);
  funTable[fd->toSignature()] = fd;
  return true;
}

ir::FuncDefn* Functory::getFunc(const std::string& name,
    const std::vector<std::shared_ptr<ir::VarDecl> > args) {
  ir::FuncDefn fd = ir::FuncDefn(true, name, NULL);
  fd.addArgs(args);
  auto element = funTable.find(fd.toSignature());
  if (element == funTable.end()) {
    return NULL;
  }
  return element->second;
}

const std::map<std::string, ir::FuncDefn*>& Functory::getAllFuncTable() const {
  return funTable;
}

} /* namespace fabrica */
} /* namespace swift */
