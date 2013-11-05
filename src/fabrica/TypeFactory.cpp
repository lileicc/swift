/*
 * TypeFactory.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#include "TypeFactory.h"

namespace swift {
namespace fabrica {
TypeFactory::TypeFactory() {
  // TODO Auto-generated constructor stub

}

TypeFactory::~TypeFactory() {
  // TODO Auto-generated destructor stub
}

bool TypeFactory::addNameTy(const std::string& name) {
  if (tyTable.find(name) != tyTable.end()) return false;
  tyTable[name] = new ir::NameTy(new ir::TypeDomain());
  return true;
}

ir::NameTy* TypeFactory::getNameTy(const std::string& name) {
  auto element = tyTable.find(name);
  if (element == tyTable.end())
    return NULL;
  return dynamic_cast<ir::NameTy*>(element->second);
}

bool TypeFactory::addInstSymbol(ir::NameTy* typ, const std::string& name) {
  //TODO
  return false;
}


}
} /* namespace swift */
