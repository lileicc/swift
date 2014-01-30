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
const ir::Ty TypeFactory::NA_TY = ir::Ty(ir::IRConstant::NA);

TypeFactory::TypeFactory() {
  // TODO Auto-generated constructor stub
  tyTable[ir::IRConstString::INT] = tyTable[ir::IRConstString::BLOG_INT] =
      &INT_TY;
  tyTable[ir::IRConstString::BOOL] = tyTable[ir::IRConstString::BLOG_BOOL] =
      &BOOL_TY;
  tyTable[ir::IRConstString::DOUBLE] = tyTable[ir::IRConstString::BLOG_DOUBLE] =
      &DOUBLE_TY;
  tyTable[ir::IRConstString::STRING] = tyTable[ir::IRConstString::BLOG_STRING] =
      &STRING_TY;
  tyTable[ir::IRConstString::NA] = &NA_TY;
}

TypeFactory::~TypeFactory() {
  // TODO Auto-generated destructor stub
  // Note: Static Element should be removed from tyTable
  tyTable.erase(ir::IRConstString::BLOG_BOOL);
  tyTable.erase(ir::IRConstString::BOOL);
  tyTable.erase(ir::IRConstString::BLOG_INT);
  tyTable.erase(ir::IRConstString::INT);
  tyTable.erase(ir::IRConstString::BLOG_DOUBLE);
  tyTable.erase(ir::IRConstString::DOUBLE);
  tyTable.erase(ir::IRConstString::BLOG_STRING);
  tyTable.erase(ir::IRConstString::STRING);
  tyTable.erase(ir::IRConstString::NA);
  // IMPORTANT:
  //   tyTable should NOT be deleted!
  //   it will be deleted by shared_ptr in blog_model!
  for (auto p : instanceTable)
    if (p.second != NULL)
      delete p.second;
  for (auto p : attrTable)
    if (p.second != NULL)
      delete p.second;
}

bool TypeFactory::addNameTy(const std::string& name) {
  if (tyTable.find(name) != tyTable.end())
    return false;
  auto ptr = std::make_shared<ir::TypeDomain>(name);
  auto ty = new ir::NameTy(ptr);
  ptr->setRefer(ty);
  tyTable[name] = ty;
  return true;
}

const ir::NameTy * TypeFactory::getNameTy(const std::string& name) const {
  auto element = tyTable.find(name);
  if (element == tyTable.end())
    return NULL;
  return dynamic_cast<const ir::NameTy*>(element->second);
}

bool TypeFactory::addInstSymbol(const ir::NameTy* typ,
    const std::string& name) {
  if (instanceTable.find(name) != instanceTable.end())
    return false;
  auto tydo = typ->getRefer();
  size_t sz = tydo->getPreLen();
  instanceTable[name] = new ir::InstSymbol(tydo, sz);
  tydo->setPreLen(sz + 1);
  tydo->setInstName(sz, name);
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

const ir::Ty * TypeFactory::getUpdateTy(ir::Ty* ty) {
  auto element = tyTable.find(ty->toString());
  if (element == tyTable.end()) {
    tyTable[ty->toString()] = ty;
    return ty;
  }
  delete ty;
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
  auto td = srcty->getRefer();
  auto oriattr = new ir::OriginAttr(name, retTy, td, td->getOriginSize());
  td->addOrigin(oriattr);
  attrTable[constructAttrSign(srcty, name)] = oriattr;
  return true;
}

bool TypeFactory::addNumberStmt(std::shared_ptr<ir::NumberStmt> numst) {
  if (numst->getRefer() != NULL) {
    numst->getRefer()->addNumberStmt(numst);
    return true;
  } else
    return false;
}

std::string TypeFactory::constructAttrSign(const ir::NameTy* srcty,
    const std::string & name) {
  return srcty->toString() + "@" + name;
}

const std::map<std::string, const ir::Ty*>& TypeFactory::getAllTyTable() const {
  return tyTable;
}

}
} /* namespace swift */
