/*
 * PFTranslator.h
 *
 *  Created on: Mar 4, 2014
 *      Author: leili
 */

#pragma once

#include "Translator.h"

namespace swift {
namespace codegen {

class PFTranslator: public swift::codegen::Translator {
public:
  PFTranslator();
  ~PFTranslator();

  virtual void translate();

protected:
  /**
   * translate the sampling algorithm
   * @return
   */
  virtual SAMPLEFUN transSampleAlg();

  /**
   * create declaration of variables/fields
   * initialization statements
   * @see Translator::createInit()
   */
  virtual void createInit();

  STATE dynamicStates;


};

} /* namespace codegen */
} /* namespace swift */
