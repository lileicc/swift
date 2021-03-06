/*
 * Functory.h
 *
 *  Created on: Nov 5, 2013
 *      Author: leili
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "../ir/Ty.h"
#include "../ir/VarDecl.h"
#include "../ir/FuncDefn.h"

namespace swift {
namespace fabrica {

/**
 * a class for creating all functions for intermediate representation
 */
class Functory {
public:
  Functory();
  ~Functory();

  /**
   * add a function with name, return type, and a list of arguments
   */
  bool addFuncDefn(const std::string& name, const ir::Ty* retTy,
      std::vector<std::shared_ptr<ir::VarDecl> > args, bool isRand, bool isExtern = false);

  /**
   * look up the table to find the function with the same signature
   * return NULL if not found
   */
  std::shared_ptr<ir::FuncDefn> getFunc(const std::string& name,
      const std::vector<std::shared_ptr<ir::VarDecl> > args);

  /**
   * get all the FuncDefn*
   */
  const std::map<std::string, std::shared_ptr<ir::FuncDefn> >& getAllFuncTable() const;
  const std::vector<std::shared_ptr<ir::FuncDefn> >& getAllFuncList() const;
private:
  std::map<std::string, std::shared_ptr<ir::FuncDefn> > funTable;
  std::vector<std::shared_ptr<ir::FuncDefn> > funList; // According to the order defined in the BLOG program
};

} /* namespace fabrica */
} /* namespace swift */
