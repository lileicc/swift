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
  void setRefer(const NameTy* ref);
  const NameTy* getRefer() const;
  void setPreLen(int l);
  int getPreLen() const;
  void addNumberStmt(std::shared_ptr<NumberStmt> num);
  const std::vector<std::shared_ptr<NumberStmt>>& getAllNumberStmt() const;
  std::shared_ptr<NumberStmt> getNumberStmt(int k) const;
  size_t getNumberStmtSize() const;
  void addOrigin(OriginAttr* o);
  const std::vector<OriginAttr*>& getAllOrigin() const;
  OriginAttr* getOrigin(int k) const;
  size_t getOriginSize() const;
  void setInstName(int k, std::string name);
  const std::string& getInstName(int k) const;
  const std::vector<std::string>& getInstNames() const;

  int getOriginID(const std::string& str);
  OriginAttr* getOrigin(const std::string& str);
private:
  std::string name;
  std::vector<std::shared_ptr<NumberStmt>> gen;
  int prelen;
  std::vector<OriginAttr*> origin;
  const NameTy* refer;
  std::vector<std::string> instName;

  std::map<std::string,int> originID;
};

}
}
