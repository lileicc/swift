/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#include "Semant.h"

namespace swift {
namespace semant {

Semant::Semant() {
  // TODO Auto-generated constructor stub

}

Semant::~Semant() {
  // TODO Auto-generated destructor stub
}

void Semant::process(absyn::BlogProgram *prog) {

}

void Semant::processTypes(absyn::BlogProgram* prog) {
  absyn::TypDecl* td;
  for (auto st : prog->getAll()) {
    td = dynamic_cast<absyn::TypDecl*>(st);
    if (td != NULL) {
      transTyDecl(td);
    }
  }
}

void Semant::transTyDecl(absyn::TypDecl* td) {
  if (!tyFactory.addNameTy(td->get().getValue())) {

  }
}

void Semant::transExpr(absyn::Expr *expr) {
  //TODO

}

void Semant::transExpr(absyn::OpExpr* expr) {
  //TODO
}

void Semant::error(int line, int col, const std::string& info) {
  errorMsg.error(line, col, info);
}

}
} /* namespace swift */
