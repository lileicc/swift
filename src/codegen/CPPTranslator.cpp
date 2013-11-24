/*
 * CPPTranslator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CPPTranslator.h"


namespace swift {
namespace codegen {

namespace {
std::string getVarOfNumType(std::string name) {
  return "__num_" + name;
}
}

static std::shared_ptr<code::QualType> INT_TYPE(new code::QualType("int"));
static std::shared_ptr<code::QualType> DOUBLE_TYPE(new code::QualType("double"));

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

std::shared_ptr<code::Code> CPPTranslator::getResult() const {
  return prog;
}

void CPPTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
  const std::string& name = td->getName();
  std::shared_ptr<code::ClassDecl> cd = code::ClassDecl::createClassDecl(coreNs, name);
  int len = td->getPreLen();
  if (len > 0) {
    std::string numvar = getVarOfNumType(name);
    code::FieldDecl::createFieldDecl(coreCls, numvar, INT_TYPE);

  }
}



} /* namespace codegen */
} /* namespace swift */




