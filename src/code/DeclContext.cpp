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
}

DeclContext::~DeclContext() {
  for (auto d : members) {
    delete d;
  }
}


void DeclContext::addDecl(Decl* decl) {
  members.push_back(decl);
}

} /* namespace code */
} /* namespace swift */
