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

namespace swift {
namespace ir {

class TypeDomain {
public:
  TypeDomain(const std::string& name = std::string());
  ~TypeDomain();

  const std::string& getName() const;
  void addRefer(NameTy* ref);
  NameTy* getRefer();
  void setPreLen(int l);
  int getPreLen();
  void addNumberStmt(NumberStmt* num);
  const std::vector<NumberStmt*>& getAllNumberStmt() const;
  NumberStmt* getNumberStmt(int k);
  size_t getNumberStmtSize();
  void addOrigin(OriginAttr* o);
  const std::vector<OriginAttr*>& getAllOrigin() const;
  OriginAttr* getOrigin(int k);
  size_t getOriginSize();
  void setInstName(int k, std::string name);
  const std::string& getInstName(int k);
  const std::vector<std::string>& getInstNames() const;

  int getOriginID(const std::string& str);
  OriginAttr* getOrigin(const std::string& str);
private:
  std::string name;
  std::vector<NumberStmt*> gen;
  int prelen;
  std::vector<OriginAttr*> origin;
  NameTy* refer;
  std::vector<std::string> instName;

  std::map<std::string,int> originID;
};

}
}
