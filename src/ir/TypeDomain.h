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

/**
 * a TypeDomain includes everything for declared type
 * its distinct symbols
 * its number statement
 * its origin functions
 * and the random functions with this type in their arguments
 */
class TypeDomain {
public:
  TypeDomain(const std::string& name = std::string());
  ~TypeDomain();

  /**
   * get the name of this declared type
   */
  const std::string& getName() const;

  /**
   * set the NameType for this TypeDomain
   */
  void setType(const NameTy* ref);

  /**
   * get the NameType for this TypeDomain
   */
  const NameTy* getType() const;

  /**
   * set the number of pre-defined distinct symbols
   */
  void setPreLen(size_t l);

  /**
   * get the number of pre-defined distinct symbols
   */
  size_t getPreLen() const;

  /**
   * add a number statement for this type
   */
  void addNumberStmt(std::shared_ptr<NumberStmt> num);

  /**
   * get all number statements for this type
   */
  const std::vector<std::shared_ptr<NumberStmt>>& getAllNumberStmt() const;

  /**
   * get k-th number statement (the index starts from 0)
   */
  std::shared_ptr<NumberStmt> getNumberStmt(size_t k) const;

  /**
   * get the number of number statements for this type
   */
  size_t getNumberStmtSize() const;

  /**
   * add an origin function declaration for this type
   */
  void addOrigin(OriginAttr* o);

  /**
   * get all origin functions for this type
   */
  const std::vector<OriginAttr*>& getAllOrigin() const;

  /**
   * get k-th origin function for this type
   */
  OriginAttr* getOrigin(size_t k) const;

  /**
   * get the number of origin functions
   */
  size_t getOriginSize() const;

  /**
   * set name of k-th distinct symbol
   */
  void setInstName(size_t k, std::string name);

  /**
   * get the name of k-th distinct symbol
   */
  const std::string& getInstName(size_t k) const;

  /**
   * get all names of declared distinct symbols
   */
  const std::vector<std::string>& getInstNames() const;

  /**
   * get the internal id of a orgin function given its function name
   * this must be signed int, since it can be -1 (not found)
   */
  int getOriginID(const std::string& str);

  /**
   * get the origin function given its function name
   * returns nullptr if not found
   */
  OriginAttr* getOrigin(const std::string& str);

  /**
   * add a random function that uses this type in the arguments
   */
  void addReferFun(std::shared_ptr<FuncDefn> fn);

  /**
   * get all functions that use this type in the arguments
   */
  std::vector<std::shared_ptr<FuncDefn> > & getReferFuns();

  /**
   * print this typedomain
   */
  void print(FILE* file, int indent);

private:
  std::string name;
  const NameTy* refer;
  std::vector<std::shared_ptr<NumberStmt>> gen;
  size_t prelen;
  std::vector<OriginAttr*> origin;
  std::vector<std::string> instName;
  std::vector<std::shared_ptr<FuncDefn> > usedBy; //all random functions that use this type domain.
  std::map<std::string, size_t> originID;
};

}
}
