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
#include "Analyzer.h"

namespace swift {
namespace analyzer {

class MCMCAnalyzer: public Analyzer{
public:
  MCMCAnalyzer(ir::BlogModel* _model = NULL);
 
  // return true when the input model is compatible with the analyzer
  virtual bool process();

  // Analysis related to number variable
  bool isOpenType(std::shared_ptr<ir::TypeDomain> ty);
  int getPropSize(std::shared_ptr<ir::TypeDomain> ty);
  std::vector<std::shared_ptr<ir::FuncDefn>>& getDependFunc(std::shared_ptr<ir::TypeDomain> ty);

private:
  std::map<std::shared_ptr<ir::TypeDomain>, int> prop_size;
  std::map<std::shared_ptr<ir::TypeDomain>, std::vector<std::shared_ptr<ir::FuncDefn>>> depend_func;
};

}
} /* namespace swift */
