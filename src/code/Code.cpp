/*
 * Code.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Code.h"

namespace swift {
namespace code {

Code::Code() {
  // TODO Auto-generated constructor stub

}

Code::~Code() {
  // TODO Auto-generated destructor stub
  for (auto p: decls)
    delete p;
  decls.clear();
  for (auto p: stmts)
    delete p;
  stmts.clear();
}

void Code::addDecl(Decl* d) {
  decls.push_back(d);
}

void Code::addStmt(Stmt* st) {
  stmts.push_back(st);
}

void Code::print(printer::CPPPrinter* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

