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
  processBodies(prog);
}

void Semant::processDeclarations(absyn::BlogProgram* prog) {
  absyn::TypDecl* td;
  absyn::DistinctDecl* dd;
  absyn::FuncDecl* fd;
  absyn::OriginDecl* od;
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

    fd = dynamic_cast<absyn::FuncDecl*>(st);
    if (fd != NULL) { // it is function declaration
      transFuncDecl(fd);
      continue;
    }

    od = dynamic_cast<absyn::OriginDecl*>(st);
    if (od != NULL) {
      transOriginDecl(od);
      continue;
    }
  }
}

void Semant::processBodies(absyn::BlogProgram* prog) {
  absyn::FuncDecl* fd;
  absyn::NumStDecl* nd;
  for (auto st : prog->getAll()) {
    fd = dynamic_cast<absyn::FuncDecl*>(st);
    if (fd != NULL) { // it is function declaration
      transFuncBody(fd);
      continue;
    }

    nd = dynamic_cast<absyn::NumStDecl*>(st);
    if (nd != NULL) {
      transNumSt(nd);
      continue;
    }
    //TODO evidence
    //TODO query

  }
}

void Semant::transTyDecl(absyn::TypDecl* td) {
  if (!tyFactory.addNameTy(td->get().getValue())) {
    error(td->line, td->col,
        "type name " + td->get().getValue() + " is defined multiple times");
  }
}

void Semant::transDistinctDecl(absyn::DistinctDecl* dd) {
  ir::NameTy* nt = lookupNameTy(dd->getTyp().getValue());
  if (nt != NULL) {
    for (size_t i = 0; i < dd->size(); i++) {
      const std::string& name = dd->getVar(i).getValue();
      int k = dd->getLen(i);
      if (k == 1) {
        if (!tyFactory.addInstSymbol(nt, name)) {
          error(dd->line, dd->col, "Symbol " + name + " already defined");
        }
      } else {
        for (int j = 0; j < k; j++) {
          if (!tyFactory.addInstSymbol(nt, arrayRefToString(name, j))) {
            error(dd->line, dd->col,
                "Symbol " + name + "[" + std::to_string(j) + "] already defined");
          }
        }
      }
    }
  }
}

void Semant::transFuncDecl(absyn::FuncDecl* fd) {
  fd->getRetTyp();
}

void Semant::transOriginDecl(absyn::OriginDecl* od) {
  //TODO
}

void Semant::transExpr(absyn::Expr *expr) {
  //TODO

}

void Semant::transExpr(absyn::OpExpr* expr) {
  //TODO
}

void Semant::transFuncBody(absyn::FuncDecl* fd) {
  //TODO
}

void Semant::transNumSt(absyn::NumStDecl* nd) {
  //TODO
}

void Semant::error(int line, int col, const std::string& info) {
  errorMsg.error(line, col, info);
}

ir::NameTy* Semant::lookupNameTy(const std::string & name) {
  return tyFactory.getNameTy(name);
}

std::string Semant::arrayRefToString(const std::string & name, int idx) {
  return name + "[" + std::to_string(idx) + "]";
}

}
} /* namespace swift */
