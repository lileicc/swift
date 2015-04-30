/*
 * ConjugacyAnalyzer.h
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

class ConjugacyAnalyzer: public Analyzer{
public:
  ConjugacyAnalyzer(std::shared_ptr<ir::BlogModel> _model = nullptr);
 
  // return true when the input model is compatible with the analyzer
  virtual bool process();

  // return the posterior distribution (gibbs distribution)
  //        nullptr when cannot handle this case
  std::shared_ptr<ir::Expr> getPosterior(std::shared_ptr<ir::FuncDefn> fun);
private:
};

}
} /* namespace swift */
