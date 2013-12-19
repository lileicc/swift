/*
 * NamespaceDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "NamespaceDecl.h"

namespace swift {
namespace code {

NamespaceDecl::NamespaceDecl(std::string name): name(name) {
  // TODO Auto-generated constructor stub

}

NamespaceDecl::~NamespaceDecl() {
  // TODO Auto-generated destructor stub
}

const std::string& NamespaceDecl::getName() {
  return name;
}

// For Printer
void NamespaceDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
