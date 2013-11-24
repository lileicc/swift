/*
 * ClassDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <memory>
#include <string>
#include "Decl.h"
#include "NamespaceDecl.h"


namespace swift {
namespace code {

class ClassDecl: public Decl, public DeclContext {
public:
  ClassDecl(std::shared_ptr<NamespaceDecl> ns, std::string name);
  ~ClassDecl();
  static std::shared_ptr<ClassDecl> createClassDecl(std::shared_ptr<NamespaceDecl> ns, const std::string & name);
};

} /* namespace code */
} /* namespace swift */
