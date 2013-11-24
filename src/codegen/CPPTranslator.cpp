/*
 * CPPTranslator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CPPTranslator.h"

namespace swift {
namespace codegen {

CPPTranslator::CPPTranslator() {
  // TODO Auto-generated constructor stub

}

CPPTranslator::~CPPTranslator() {
  // TODO Auto-generated destructor stub
}

void CPPTranslator::translate(swift::ir::BlogModel* model) {
  for (auto ty : model->getTypes())
    transTypeDomain(ty);
}

code::Code* CPPTranslator::getResult() const {
}

void CPPTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
}

} /* namespace codegen */
} /* namespace swift */
