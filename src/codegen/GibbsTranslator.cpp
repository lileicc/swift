/*
 * GibbsTranslator.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: yiwu
 */

#include <cassert>
#include <iostream>


#include "GibbsTranslator.h"

namespace swift {
namespace codegen {

// BayesVar Method Name
const std::string GibbsTranslator::MCMC_Global_GibbsAlgo_MethodName = "gibbs_resample_arg";
const std::string GibbsTranslator::MCMC_Global_GibbsConjugateAlgo_MethodName = "conjugate_gibbs_resample_arg";
const std::string GibbsTranslator::MCMC_CalcPosterior_MethodName = "conjugacy_analysis";
const std::string GibbsTranslator::MCMC_GetSupport_MethodName = "get_all_vals";

// BayesVar member variable
const std::string GibbsTranslator::MCMC_AllVal_VarName = "all_vals";

// Temp variable
const std::string GibbsTranslator::TEMP_NXT_VAL_NAME = "_nxt_val";

// Util Func Name
const std::string GibbsTranslator::UtilUpdateRangeFuncName = "_util_update_range";

///////////////////////////////////////////////////////////////
//  Util Functions for Gibbs Sampling
///////////////////////////////////////////////////////////////

/////////////// END of Util Functions ///////////////////

GibbsTranslator::GibbsTranslator() {
  MHTranslator();
  conjugacy_analyzer = NULL;
}

GibbsTranslator::~GibbsTranslator() {
  if(conjugacy_analyzer != NULL) delete conjugacy_analyzer;
}

bool GibbsTranslator::init_GibbsTranslator(std::shared_ptr<swift::ir::BlogModel> model) {
  if(!init_MHTranslator(model)) return false;
  
  conjugacy_analyzer = new analyzer::ConjugacyAnalyzer(model);
  if(!contig_analyzer->process()) {
    delete prog;
    prog = NULL;
    return false;
  }
  
  return true;
}


/////////////////////////////////////////
////// main process start from here
//////////////////////////////////////////

void GibbsTranslator::translate(std::shared_ptr<swift::ir::BlogModel> model) {

  if (!init_GibbsTranslator(model)) return ;
  
  translate_fixed_part();

  translate_mcmc_data_structure();

  // set the sample algorithm selected for the MCMC framework
  setSampleAlgorithm();

  // create initStorage() and GarbageCollect()
  createStorageInit();
  
  translate_mcmc_obj_methods();

  translate_mcmc_query_evidences();

  // translate sampleAlg and main
  transSampleAlg();
  createMain();

  if (!errorMsg.Okay()) prog = NULL;
}

///////////////////////////////////////////////////////////////
////////////// high level translate() ends here ///////////////
///////////////////////////////////////////////////////////////

code::Code* GibbsTranslator::getResult() {
  if (!errorMsg.Okay()) return NULL;

  useTag = true;
  return prog;
}

void GibbsTranslator::setSampleAlgorithm() {
  // Set Algorithm for NumberVariable
  for (auto& ty : model->getTypes()) {
    if (ty->getAllNumberStmt().size() > 0) {

      // TODO: for number variable, we do not support gibbs sampling!

      std::string name = ty->getName();
      varMethods[name][MCMC_Resample_MethodName]->addStmt(
        new code::CallExpr(
          new code::Identifier(MCMC_Global_MHNumVarAlgo_MethodName),
          std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
    }
  }

  // Set Algorithm for Normal Random Variable
  for (auto& fun : model->getRandFuncs()) {
    std::string name = fun->getName();
    auto&mp = varMethods[name];
    std::string sample_algo_name = MCMC_Global_MHAlgo_MethodName; // by default, using MH algorithm

    // Check Finite Support
    auto ty = dynamic_cast<const ir::NameTy*>(fun->getRetTyp());
    if (ty != NULL) {
      sample_algo_name = MCMC_Global_GibbsAlgo_MethodName;

      // compute the support
      auto ref = ty->getRefer();
      if (ref->getNumberStmtSize() == 0) {
        // add init statement to constructor
        mp[name]->addStmt(new code::CallExpr(
          new code::Identifier(UtilUpdateRangeFuncName),
          std::vector<code::Expr*>{new code::Identifier(MCMC_AllVal_VarName), new code::IntegerLiteral(ref->getPreLen())}));
      }
      else {
        // register get_all_vals() methods
        auto clsdef = bayesVars[name];
        auto f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_GetSupport_MethodName, INT_VECTOR_REF_TYPE);
        std::string storename = getStoreOfNumberVar(ref->getName());
        f_ptr->addStmt(new code::CallExpr(
          new code::Identifier(UtilUpdateRangeFuncName),
          std::vector<code::Expr*>{
            new code::Identifier(MCMC_AllVal_VarName),
            createPtrMethodCall(new code::Identifier(storename), MCMC_GetVal_MethodName)
          }
        ));
        f_ptr->addStmt(new code::ReturnStmt(new code::Identifier(MCMC_AllVal_VarName)));
        mp[MCMC_GetSupport_MethodName] = f_ptr;
      }
    }
    else { // is not NameTy
      auto clsdef = bayesVars[name];
      auto f_ptr = code::FunctionDecl::createFunctionDecl(clsdef, MCMC_CalcPosterior_MethodName, VOID_TYPE);
      code::Type clsRefTy = mapIRTypeToCodeType(fun->getRetTyp());
      clsRefTy.setRef(true);
      f_ptr->setParams(std::vector<code::ParamVarDecl*>{new code::ParamVarDecl(NULL,TEMP_NXT_VAL_NAME,clsRefTy)});
      mp[MCMC_CalcPosterior_MethodName] = f_ptr;

      // check conjugacy
      auto post = conjugacy_analyzer->getPosterior(fun);
      if (post != nullptr) { // posterior distribution can be analytically computed
        sample_algo_name = MCMC_Global_GibbsConjugateAlgo_MethodName;

        cur_constructor = &f_ptr->getBody();
        cur_context = coreNs; // need to register posterior distributions
        cur_method_name = MCMC_GetVal_MethodName;
        f_ptr->addStmt(new code::BinaryOperator(
          new code::Identifier(TEMP_NXT_VAL_NAME),
          transExpr(post),
          code::OpKind::BO_ASSIGN)); // set conjugacy_analysis()
        cur_constructor = NULL;
      }
      else {
        // Conjugacy Checking Failure

        // Check if special built-in proposal can be applied
        if (config->getBoolValue("USE_GAUSSIAN_PROPOSAL") &&
          fun->getRetTyp()->getTyp() == ir::IRConstant::DOUBLE) {
          // Using Gaussian Proposal
          errorMsg.warning(-1, -1, "[GibbsTranslator]: Conjugacy Analysis Failed for Random Function <" + name + ">! Default sampling algorithm will be [MH with Gaussian Proposal]!.");
          varMethods[name][MCMC_Resample_MethodName]->addStmt(
            new code::CallExpr(
            new code::Identifier(MCMC_Global_MHAlgo_SymProp_MethodName), 
            std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS), new code::Identifier(UtilPropUniGaussName)}));
          continue;
        }

        errorMsg.warning(-1,-1,"[GibbsTranslator]: Conjugacy Analysis Failed for Random Function <"+name+">! Default sampling algorithm will be [Parental MH]!\n"+
          "   >> Tip: You can manually write method *[" + MCMC_CalcPosterior_MethodName + "]* to sample from the posterior distribution and uncomment the method call in ["+MCMC_Resample_MethodName+"].");

        varMethods[name][MCMC_Resample_MethodName]->addStmt(
          new code::CallExpr(
          new code::Identifier(MCMC_Global_MHAlgo_MethodName), // add this commented method call in the resample method
          std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
        continue;
      }
    }

    // Set Sample Method
    varMethods[name][MCMC_Resample_MethodName]->addStmt(
      new code::CallExpr(
        new code::Identifier(sample_algo_name),
        std::vector<code::Expr*>{new code::Identifier(KEYWORD_THIS)}));
  }
}


/////////////// Translation of clause and expression ////////////////////////


} /* namespace codegen */
} /* namespace swift */

