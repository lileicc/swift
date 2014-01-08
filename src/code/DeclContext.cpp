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
  // TODO: do we need to test NULL, seems not necessary
  for (auto d : members) {
    delete d;
  }
}

Decl* DeclContext::getMem(int k) {
  return members[k];
}

std::vector<Decl*>& DeclContext::getAllMem() {
  return members;
}

void DeclContext::addDecl(Decl* decl) {
  members.push_back(decl);
}

} /* namespace code */
} /* namespace swift */
