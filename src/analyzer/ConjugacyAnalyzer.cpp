/*
 * ConjugacyAnalyzer.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#include "ConjugacyAnalyzer.h"

#include "ConjugatePriors/ConjugatePriorList.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>

#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

//////////// Util Constant //////////////////
const std::string ConjugacyAnalyzer::NXT_VAL_NAME = "_nxt_val";
const std::string ConjugacyAnalyzer::CHILD_SET_NAME = "child";
const std::string ConjugacyAnalyzer::SAMPLE_METHOD_NAME = "sample";
/////////////////////////////////////////////

ConjugacyAnalyzer::ConjugacyAnalyzer(std::shared_ptr<ir::BlogModel> _model)
  : Analyzer(_model) {
  contig_analyzer = NULL;
  self_declared = false;
}

ConjugacyAnalyzer::~ConjugacyAnalyzer() {
  if (self_declared) {
    self_declared = false;
    delete contig_analyzer;
  }
}

void ConjugacyAnalyzer::set_contig_analyzer(ContigAnalyzer* ptr) {
  if (self_declared) {
    delete contig_analyzer;
    self_declared = false;
  }
  contig_analyzer = ptr;
}

bool ConjugacyAnalyzer::process() {

  // We need to make sure that we have a contig_analyzer
  if (contig_analyzer == NULL) {
    self_declared = true;
    contig_analyzer = new ContigAnalyzer(model);
    if (!contig_analyzer->process()) return false;
  }

  // get function dependency
  // We will ONLY process random function
  childFuncs.clear();
  for (auto& fun : model->getRandFuncs()) {
    auto& parent_funcs = contig_analyzer->getReferredFunc(fun->getBody());
    for (auto&p_f : parent_funcs)
      childFuncs[p_f].insert(fun);
  }

  // Compute Posterior Distributions
  posterior.clear();
  auto& priors = conjugate::ConjugatePriorList::priorStore;
  for (auto& fun : model->getRandFuncs()) {
    // check finite support
    if (isFiniteSupport(fun)) continue; // finte support can be generally handled

    // TODO: to handle if/case stmt or general expression
    if (std::dynamic_pointer_cast<ir::Distribution>(fun->getBody()) == nullptr) continue;
    
    if (childFuncs[fun].size() == 0) { // pure prior distribution
      posterior[fun] = std::dynamic_pointer_cast<ir::Expr>(fun->getBody());
      continue;
    }

    // TODO: allow multiple type of children
    if (childFuncs[fun].size() > 1) {
      // Currently we only allow one child functions for each random variable
      //  --> for multiple children, the gibbs distribution will be a product of different distributions!
      continue;
    }

    // For now, we only handle pure distribution as function body
    auto dist = std::dynamic_pointer_cast<ir::Distribution>(fun->getBody());
    for (auto& c : priors[dist->getDistrName()]) {
      auto post = c->process(fun, childFuncs[fun]);
      if (post != nullptr) {
        // successfully analyzed!
        posterior[fun] = post;
        break;
      }
    }
  }

  if (!errMsg.Okay()) {
    return false;
  }

  return true;
}

std::shared_ptr<ir::Expr> ConjugacyAnalyzer::getPosterior(std::shared_ptr<ir::FuncDefn> fun) {
  if (posterior.count(fun) == 0) return nullptr;
  return posterior[fun];
}

//////////////////////////////////////
///       Util Functions
//////////////////////////////////////

bool ConjugacyAnalyzer::isFiniteSupport(std::shared_ptr<ir::FuncDefn> fun) {
  auto ty = dynamic_cast<const ir::NameTy*>(fun->getRetTyp());
  if (ty != NULL)
    return true; // Currently we only apply a coarse checking for support
  return false;
}

}
} /* namespace swift */
