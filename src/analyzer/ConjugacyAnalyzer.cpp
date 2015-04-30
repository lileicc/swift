/*
 * ConjugacyAnalyzer.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#include "ConjugacyAnalyzer.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>

#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

ConjugacyAnalyzer::ConjugacyAnalyzer(std::shared_ptr<ir::BlogModel> _model)
  : Analyzer(_model) {
}

bool ConjugacyAnalyzer::process() {

  if (!errMsg.Okay()) {
    return false;
  }

  return true;
}

std::shared_ptr<ir::Expr> ConjugacyAnalyzer::getPosterior(std::shared_ptr<ir::FuncDefn> fun) {
  // TODO: to add analysis of conjugate distributions
  return nullptr;
}

}
} /* namespace swift */
