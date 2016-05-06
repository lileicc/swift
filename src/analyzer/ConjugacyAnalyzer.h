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
#include "ContigAnalyzer.h"

namespace swift {
namespace analyzer {

class ConjugacyAnalyzer: public Analyzer{
public:
  ConjugacyAnalyzer(std::shared_ptr<ir::BlogModel> _model = nullptr);
  ~ConjugacyAnalyzer();

  void set_contig_analyzer(ContigAnalyzer* ptr);

  // return true when the input model is compatible with the analyzer
  virtual bool process();

  // return the posterior distribution (gibbs distribution)
  //        nullptr when cannot handle this case
  std::shared_ptr<ir::Expr> getPosterior(std::shared_ptr<ir::FuncDefn> fun);

  //////////////////////
  /// Util Functions
  //////////////////////
  bool isFiniteSupport(std::shared_ptr<ir::FuncDefn> fun);

private:
  bool self_declared;
  ContigAnalyzer* contig_analyzer;

  std::map<std::shared_ptr<ir::FuncDefn>, std::set<std::shared_ptr<ir::FuncDefn>>> childFuncs;

  std::map<std::shared_ptr<ir::FuncDefn>, std::shared_ptr<ir::Expr>> posterior;


  ////////////////////////////////////////////////
  //// Util Constant
  ////////////////////////////////////////////////
  static const std::string NXT_VAL_NAME;
  static const std::string CHILD_SET_NAME;
  static const std::string SAMPLE_METHOD_NAME;
};

}
} /* namespace swift */
