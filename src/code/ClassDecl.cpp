/*
 * ClassDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ClassDecl.h"

namespace swift {
namespace code {

ClassDecl::ClassDecl(DeclContext* ns, std::string name) :
    parent(ns), name(name) {
}

ClassDecl::~ClassDecl() {
}

ClassDecl* ClassDecl::createClassDecl(DeclContext* ns,
    const std::string& name) {
  ClassDecl* cd = new ClassDecl(ns, name);
  ns->addDecl(cd);
  return cd;
}

const std::string& ClassDecl::getName() const {
  return name;
}

// For Printer
void ClassDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
