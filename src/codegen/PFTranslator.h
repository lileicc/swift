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

protected:
  /**
   *
   * @return
   */
  virtual code::FunctionDecl* transSampleAlg();
};

} /* namespace codegen */
} /* namespace swift */
