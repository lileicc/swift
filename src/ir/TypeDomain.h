/*
 * TypeDomain.h
 *
 *  Created on: Nov 2, 2013
 *      Author: yiwu
 */
#pragma once
#include <map>
#include <string>
#include <vector>

#include "IRForwardDecl.h"

#include "OriginAttr.h"
#include "Ty.h"
#include "NameTy.h"
#include "NumberStmt.h"

namespace swift {
namespace ir {

class TypeDomain {
public:
  TypeDomain(const std::string& name = std::string());
  ~TypeDomain();

  const std::string& getName();
  void addRefer(NameTy* ref);
  NameTy* getRefer();
  void setPreLen(int l);
  int getPreLen();
  void addNumberStmt(NumberStmt* num);
  const std::vector<NumberStmt*>& getAllNumberStmt();
  NumberStmt* getNumberStmt(int k);
  size_t getNumberStmtSize();
  void addOrigin(OriginAttr* o);
  const std::vector<OriginAttr*>& getAllOrigin();
  OriginAttr* getOrigin(int k);
  size_t getOriginSize();

  int getOriginID(const std::string& str);
  OriginAttr* getOrigin(const std::string& str);
private:
  std::string name;
  std::vector<NumberStmt*> gen;
  int prelen;
  std::vector<OriginAttr*> origin;
  NameTy* refer;

  std::map<std::string,int> originID;
};

}
}
