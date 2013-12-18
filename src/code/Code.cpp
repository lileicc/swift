/*
 * Code.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Code.h"
#include "../printer/CPPPrinter.h"

namespace swift {
namespace code {

Code::Code() {
  // TODO Auto-generated constructor stub

}

Code::~Code() {
  // TODO Auto-generated destructor stub
}

void Code::addDecl(Decl* d) {
  decls.addDecl(d);
}

void Code::addStmt(Stmt* st) {
  stmts.addStmt(st);
}

DeclContext& Code::getDecls() {
  return decls;
}

CompoundStmt& Code::getStmts() {
  return stmts;
}

void Code::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

