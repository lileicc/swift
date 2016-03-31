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
}

Functory::~Functory() {
  // Note: We DO NOT Need to delete all the pointers to FuncDefn here!
}

bool Functory::addFuncDefn(const std::string& name, const ir::Ty * retTy,
    std::vector<std::shared_ptr<ir::VarDecl> > args, bool isRand, bool isExtern) {
  if (getFunc(name, args) != NULL)
    return false;
  std::shared_ptr<ir::FuncDefn> fd = std::make_shared<ir::FuncDefn>(isRand,
      std::string(name), retTy, isExtern);
  fd->setArgs(args);
  funTable[fd->toSignature()] = fd;
  funList.push_back(fd);
  return true;
}

std::shared_ptr<ir::FuncDefn> Functory::getFunc(const std::string& name,
    const std::vector<std::shared_ptr<ir::VarDecl> > args) {
  ir::FuncDefn fd = ir::FuncDefn(true, name, NULL);
  fd.setArgs(args);
  auto element = funTable.find(fd.toSignature());
  if (element == funTable.end()) {
    return nullptr;
  }
  return element->second;
}

const std::map<std::string, std::shared_ptr<ir::FuncDefn> >& Functory::getAllFuncTable() const {
  return funTable;
}

const std::vector<std::shared_ptr<ir::FuncDefn> >& Functory::getAllFuncList() const {
  return funList;
}

} /* namespace fabrica */
} /* namespace swift */
