/*
 * LWTranslator.h
 *
 *  Created on: Mar 4, 2014
 *      Author: leili
 */

#pragma once

#include "Translator.h"

namespace swift {
namespace codegen {

class LWTranslator: public swift::codegen::Translator {
public:
  LWTranslator();
  ~LWTranslator();
};

} /* namespace codegen */
} /* namespace swift */
