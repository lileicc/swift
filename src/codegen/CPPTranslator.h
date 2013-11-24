/*
 * CPPTranslator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include "../ir/IRHeader.h"
#include "../code/Code.h"

namespace swift {
namespace codegen {

class CPPTranslator {
public:
  CPPTranslator();
  virtual ~CPPTranslator();
  void translate(swift::ir::BlogModel* model);
  code::Code* getResult() const;

private:
  std::shared_ptr<code::Code> prog; // holder for result target code
  void transTypeDomain(std::shared_ptr<ir::TypeDomain> td);
};

} /* namespace codegen */
} /* namespace swift */

