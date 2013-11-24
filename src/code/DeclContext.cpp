/*
 * DeclContext.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "DeclContext.h"

namespace swift {
namespace code {

DeclContext::DeclContext() {
  // TODO Auto-generated constructor stub

}

DeclContext::~DeclContext() {
  // TODO Auto-generated destructor stub
}


void DeclContext::addDecl(std::shared_ptr<Decl> decl) {
  members.push_back(decl);
}

} /* namespace code */
} /* namespace swift */
