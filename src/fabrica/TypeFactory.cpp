/*
 * TypeFactory.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#include "TypeFactory.h"

namespace swift {
namespace fabrica {

const ir::Ty TypeFactory::INT_TY = ir::Ty(ir::IRConstant::INT);
const ir::Ty TypeFactory::BOOL_TY = ir::Ty(ir::IRConstant::BOOL);
const ir::Ty TypeFactory::DOUBLE_TY = ir::Ty(ir::IRConstant::DOUBLE);
const ir::Ty TypeFactory::STRING_TY = ir::Ty(ir::IRConstant::STRING);

TypeFactory::TypeFactory() {
  // TODO Auto-generated constructor stub
  tyTable[INT_TY.toString()] = &INT_TY;
  tyTable[BOOL_TY.toString()] = &BOOL_TY;
  tyTable[DOUBLE_TY.toString()] = &DOUBLE_TY;
  tyTable[STRING_TY.toString()] = &STRING_TY;
}

TypeFactory::~TypeFactory() {
  // TODO Auto-generated destructor stub
}

bool TypeFactory::addNameTy(const std::string& name) {
  if (tyTable.find(name) != tyTable.end())
    return false;
  tyTable[name] = new ir::NameTy(new ir::TypeDomain());
  return true;
}

const ir::NameTy * TypeFactory::getNameTy(const std::string& name) const {
  auto element = tyTable.find(name);
  if (element == tyTable.end())
    return NULL;
  return dynamic_cast<ir::NameTy const*>(element->second);
}

bool TypeFactory::addInstSymbol(const ir::NameTy* typ,
    const std::string& name) {
  if (instanceTable.find(name) != instanceTable.end())
    return false;
  ir::TypeDomain* tydo = typ->getRefer();
  int sz = tydo->getPreLen();
  instanceTable[name] = new ir::InstSymbol(tydo, sz);
  tydo->setPreLen(++sz);
  return true;
}

const ir::InstSymbol * TypeFactory::getInstSymbol(
    const std::string& name) const {
  auto element = instanceTable.find(name);
  if (element == instanceTable.end())
    return NULL;
  return element->second;
}

const ir::Ty * TypeFactory::getTy(const std::string& name) const {
  auto element = tyTable.find(name);
  if (element == tyTable.end())
    return NULL;
  return element->second;
}

const ir::OriginAttr * TypeFactory::getOriginAttr(const ir::NameTy* srcty,
    const std::string& name) const {
  auto element = attrTable.find(constructAttrSign(srcty, name));
  if (element == attrTable.end()) {
    return NULL;
  }
  return element->second;
}

bool TypeFactory::addOriginAttr(const ir::NameTy * srcty,
    const ir::NameTy* retTy, const std::string& name) {
  if (getOriginAttr(srcty, name) != NULL) {
    return false;
  }
  ir::TypeDomain* td = srcty->getRefer();
  ir::OriginAttr* oriattr = new ir::OriginAttr(name, retTy, td, td->getOriginSize());
  td->addOrigin(oriattr);
  attrTable[ constructAttrSign(srcty, name) ] = oriattr;
  return true;
}

std::string TypeFactory::constructAttrSign(const ir::NameTy* srcty, const std::string & name) {
  return srcty->toString() + "@" + name;
}

}
} /* namespace swift */
