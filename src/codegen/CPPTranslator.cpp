/*
 * CPPTranslator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CPPTranslator.h"


namespace swift {
namespace codegen {

std::shared_ptr<code::QualType> CPPTranslator::INT_TYPE(new code::QualType("int"));
std::shared_ptr<code::QualType> CPPTranslator::DOUBLE_TYPE(new code::QualType("double"));
std::shared_ptr<code::QualType> CPPTranslator::STRING_TYPE(new code::QualType("std::string"));
std::string CPPTranslator::DISTINCT_FIELDNAME = "__name_";

namespace {
std::string getVarOfNumType(std::string name) {
  return "__num_" + name;
}
}

CPPTranslator::CPPTranslator() {
  // TODO Auto-generated constructor stub

}

CPPTranslator::~CPPTranslator() {
  // TODO Auto-generated destructor stub
}

void CPPTranslator::translate(swift::ir::BlogModel* model) {
  for (auto ty : model->getTypes())
    transTypeDomain(ty);
  for (auto fun : model->getRandFuncs())
    transFun(fun);
}

code::Code* CPPTranslator::getResult() const {
  return prog;
}

void CPPTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
  const std::string& name = td->getName();
  code::ClassDecl* cd = code::ClassDecl::createClassDecl(coreNs, name);
  code::FieldDecl::createFieldDecl(cd, DISTINCT_FIELDNAME, STRING_TYPE);
  int len = td->getPreLen();
  if (len > 0) {
    std::string numvar = getVarOfNumType(name);
    code::FieldDecl* fd = code::FieldDecl::createFieldDecl(coreCls, numvar, INT_TYPE);
    coreClsInit->addStmt(new code::BinaryOperator(new code::VarRef(numvar), new code::IntegerLiteral(len), code::OpKind::BO_ASSIGN) );
    // TODO please add the corresponding distinct name
  }
}

void CPPTranslator::transFun(std::shared_ptr<ir::FuncDefn> td) {
  // TODO add sampleing function and likelihood calculation function
}

} /* namespace codegen */
} /* namespace swift */




