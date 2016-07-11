/*
 * GibbsTranslator.h
 *
 *  Created on: Apr 29, 2015
 *      Author: yiwu
 */

#pragma once

#include "MHTranslator.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include "../analyzer/ConjugacyAnalyzer.h"

namespace swift {
namespace codegen {

class GibbsTranslator: public MHTranslator {
public:
  GibbsTranslator();
  virtual ~GibbsTranslator();
  void translate(std::shared_ptr<swift::ir::BlogModel> model);
  code::Code* getResult();
  
protected:
  /*
   * Translation Steps called in translate()
   */
  virtual bool init_GibbsTranslator(std::shared_ptr<swift::ir::BlogModel> model);

  analyzer::ConjugacyAnalyzer* conjugacy_analyzer;

  // BayesVar Method Name
  static const std::string MCMC_Global_GibbsAlgo_MethodName;
  static const std::string MCMC_Global_GibbsConjugateAlgo_MethodName;
  static const std::string MCMC_CalcPosterior_MethodName;
  static const std::string MCMC_GetSupport_MethodName;

  // BayesVar member variable
  static const std::string MCMC_AllVal_VarName;

  // Temp variable
  static const std::string TEMP_NXT_VAL_NAME;

  // Util Func Name
  static const std::string UtilUpdateRangeFuncName;
  

  ////////////////////////////////////////////////
  // Util Functions for Gibbs
  ////////////////////////////////////////////////
  

  ///////////////////////////////////////////////////////////////////
  //     Core methods start from here
  ///////////////////////////////////////////////////////////////////

  // set function call in the method of mcmc_resample()
  virtual void setSampleAlgorithm();

  ////////////////////////////////////////////////////////
  // Global Flag
  
  /////////////////////////////////////////////////////////

};

} /* namespace codegen */
} /* namespace swift */

