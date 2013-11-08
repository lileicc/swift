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
}

bool Functory::addFuncDefn(const std::string& name, const ir::Ty* retTy,
    std::vector<const std::shared_ptr<ir::VarDecl> > args, bool isRand) {
  if (getFunc(name, args) != NULL) return false;
  ir::FuncDefn* fd = new ir::FuncDefn(isRand, std::string(name), retTy);
  funTable[fd->toSignature()] = fd;
  return true;
}

ir::FuncDefn* Functory::getFunc(const std::string& name,
    const std::vector<const std::shared_ptr<ir::VarDecl> > args) {
  ir::FuncDefn fd = ir::FuncDefn(true, name, NULL);
  auto element = funTable.find(fd.toSignature());
  if (element == funTable.end()) {
    return NULL;
  }
  return element->second;
}

} /* namespace fabrica */
} /* namespace swift */
