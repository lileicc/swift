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
  void setPreLen(size_t l);
  size_t getPreLen() const;
  void addNumberStmt(std::shared_ptr<NumberStmt> num);
  const std::vector<std::shared_ptr<NumberStmt>>& getAllNumberStmt() const;
  std::shared_ptr<NumberStmt> getNumberStmt(size_t k) const;
  size_t getNumberStmtSize() const;
  void addOrigin(OriginAttr* o);
  const std::vector<OriginAttr*>& getAllOrigin() const;
  OriginAttr* getOrigin(size_t k) const;
  size_t getOriginSize() const;
  void setInstName(size_t k, std::string name);
  const std::string& getInstName(size_t k) const;
  const std::vector<std::string>& getInstNames() const;
  // this must be signed int, since it can be -1 (not found)
  int getOriginID(const std::string& str);
  OriginAttr* getOrigin(const std::string& str);
  void addReferFun(std::shared_ptr<FuncDefn> fn);
  std::vector<std::shared_ptr<FuncDefn> > & getReferFuns();
  void print(FILE* file, int indent);

private:
  std::string name;
  std::vector<std::shared_ptr<NumberStmt>> gen;
  size_t prelen;
  std::vector<OriginAttr*> origin;
  const NameTy* refer;
  std::vector<std::string> instName;
  std::vector<std::shared_ptr<FuncDefn> > usedBy; //all random functions that use this type domain.
  std::map<std::string, size_t> originID;
};

}
}
