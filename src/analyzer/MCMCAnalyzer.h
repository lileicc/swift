/*
 * MCMCAnalyzer.h
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#pragma once

#include <map>
#include <memory>
#include <vector>
#include <set>
#include "Analyzer.h"

namespace swift {
namespace analyzer {

class MCMCAnalyzer: public Analyzer{
public:
  MCMCAnalyzer(std::shared_ptr<ir::BlogModel> _model = nullptr);
 
  // return true when the input model is compatible with the analyzer
  virtual bool process();

  // Analysis related to number variable
  /*
   * check whether this type is open-type
   */
  bool isOpenType(std::shared_ptr<ir::TypeDomain> ty);
  /*
   * check whether this function has an argument of open-type
   */
  bool isPropertyFunc(std::shared_ptr<ir::FuncDefn> fun);
  int getPropSize(std::shared_ptr<ir::TypeDomain> ty);
  std::vector<std::shared_ptr<ir::FuncDefn>>& getDependFunc(std::shared_ptr<ir::TypeDomain> ty);

private:
  std::map<std::shared_ptr<ir::TypeDomain>, int> prop_size;
  std::map<std::shared_ptr<ir::TypeDomain>, std::vector<std::shared_ptr<ir::FuncDefn>>> depend_func;
  std::set<std::shared_ptr<ir::FuncDefn>> prop_fun;
};

}
} /* namespace swift */
