/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#include "Clause.h"

namespace swift {
namespace ir {
Clause::Clause() {

}

void Clause::setType(Type* ty) {
  this->ty = ty;
}

}
}
