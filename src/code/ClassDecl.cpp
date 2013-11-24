/*
 * ClassDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ClassDecl.h"


namespace swift {
namespace code {

ClassDecl::ClassDecl(std::shared_ptr<NamespaceDecl> ns, std::string name) {
  // TODO Auto-generated constructor stub

}

ClassDecl::~ClassDecl() {
  // TODO Auto-generated destructor stub
}



std::shared_ptr<ClassDecl> ClassDecl::createClassDecl(std::shared_ptr<NamespaceDecl> ns, const std::string& name) {
  std::shared_ptr<ClassDecl> cd(new ClassDecl(ns, name));
  ns->addDecl(cd);
  return cd;
}

} /* namespace code */
} /* namespace swift */
