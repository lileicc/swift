/*
 * Preprocessor.h
 *
 *  Created on: Feb 18, 2014
 *      Author: yiwu
 */

#pragma once
#include <cstdio>
#include <memory>
#include <string>
#include "../absyn/BlogProgram.h"
#include "../msg/ErrorMsg.h"

namespace swift {
namespace preprocess {

class Preprocessor {
public:
  Preprocessor();
  ~Preprocessor();
  void process(absyn::BlogProgram* prog);
  bool Okay();
  absyn::BlogProgram* getProg();
private:

  // assume that fun->getname() == "EXPAND"
  // @return: return empty vector when there is some error using EXPAND macro
  //     NOTE: fun will not be deleted!
  std::vector<absyn::Expr*> parse_macro_EXPAND(absyn::FuncApp* fun);

  // parse the expression tree
  // @return: NULL if expr remains unchanged, 
  //          o.w. return the new expression, the old expr will be deleted
  absyn::Expr* parse_expr(absyn::Expr* expr);

  // process and expand all the macros defined in the program
  void processMacro(absyn::BlogProgram*& prog);

  /**
  * process set evidence
  *    i.e.  obs {T t} = {t1,t2}
  * :::=>
  *      obs #{T t} = 2;
  *      random t1 ~ UniformChoice({T t});
  *      random t2 ~ UniformChoice({T t: t1 != t2})
  */
  void processSetEvidence(absyn::BlogProgram*& prog);

  void error(int line, int col, std::string info);
  void warning(int line, int col, std::string info);

  msg::ErrorMsg errorMsg;
  absyn::BlogProgram* blogProg;
};

}
} /* namespace swift */
