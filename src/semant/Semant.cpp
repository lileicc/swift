/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#include "Semant.h"

namespace swift {
namespace semant {

Semant::Semant() :
    errorMsg(stderr) {
  // TODO Auto-generated constructor stub

}

Semant::~Semant() {
  // TODO Auto-generated destructor stub
}

void Semant::process(absyn::BlogProgram* prog) {
  processDeclarations(prog);
}

void Semant::processDeclarations(absyn::BlogProgram* prog) {
  absyn::TypDecl* td;
  absyn::DistinctDecl* dd;
  for (auto st : prog->getAll()) {
    td = dynamic_cast<absyn::TypDecl*>(st);
    if (td != NULL) { // it is type declaration
      transTyDecl(td);
      continue;
    }

    dd = dynamic_cast<absyn::DistinctDecl*>(st);
    if (dd != NULL) { // it is distinct declaration
      transDistinctDecl(dd);
      continue;
    }
  }
}

void Semant::transTyDecl(absyn::TypDecl* td) {
  if (!tyFactory.addNameTy(td->get().getValue())) {
    error(td->line, td->col,
        "type name " + td->get().getValue() + " is defined multiple times");
  }
}

void Semant::transDistinctDecl(absyn::DistinctDecl* dd) {
  // TODO

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
