/*
 * CallClassConstructor.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: leili
 */

#include "CallClassConstructor.h"

namespace swift {
namespace code {

CallClassConstructor::CallClassConstructor(Type type, std::vector<Expr*> args) : Expr(args), type(type) {
}

CallClassConstructor::~CallClassConstructor() {
}
  
Type& CallClassConstructor::getType() {
  return type;
}
  
void CallClassConstructor::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
