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
