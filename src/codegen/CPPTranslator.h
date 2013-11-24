/*
 * CPPTranslator.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "../ir/IRHeader.h"
#include "../code/Code.h"


namespace swift {
namespace codegen {

class CPPTranslator {
public:
  CPPTranslator();
  virtual ~CPPTranslator();
  void translate(swift::ir::BlogModel* model);
  std::shared_ptr<code::Code> getResult() const;

private:
  std::shared_ptr<code::Code> prog; // holder for result target code
  std::shared_ptr<code::ClassDecl> coreCls; // main Class for the sampler;
  std::shared_ptr<code::NamespaceDecl> coreNs; // main namespace
  std::shared_ptr<code::MethodDecl> coreClsInit; // init function for main class
  void transTypeDomain(std::shared_ptr<ir::TypeDomain> td);

  static std::shared_ptr<code::QualType> INT_TYPE;
  static std::shared_ptr<code::QualType> DOUBLE_TYPE;

};

} /* namespace codegen */
} /* namespace swift */

