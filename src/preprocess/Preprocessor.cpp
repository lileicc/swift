/*
 * Preprocessor.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: yiwu
 */

#include "Preprocessor.h"

#include <memory>
#include <utility>

namespace swift {
namespace preprocess {

Preprocessor::Preprocessor() :
    errorMsg(stderr), blogProg(NULL), isResultUsed(false) {
}

Preprocessor::~Preprocessor() {
  if (!isResultUsed) delete blogProg;
}

void Preprocessor::process(absyn::BlogProgram* prog) {
  blogProg = prog;
  // Process Set Evidence
  processSetEvidence(blogProg);
}

void Preprocessor::processSetEvidence(absyn::BlogProgram*& prog) {
  // Note: It is reference here! We have to modify the BLOG program!
  std::vector<absyn::Stmt*>& all = prog->getAllRef();
  for (size_t i = 0; i < all.size(); ++i) {
    absyn::Evidence* ev = dynamic_cast<absyn::Evidence*>(all[i]);
    if (ev == NULL) continue;
    absyn::CondSet* lt = dynamic_cast<absyn::CondSet*>(ev->getLeft());
    absyn::ListSet* rt = dynamic_cast<absyn::ListSet*>(ev->getRight());
    if (lt == NULL || rt == NULL) continue;
    int line = rt->line, col = rt->col;
    // Set Evidence: obs {CondSet} = {ListSet}
    // :::=> obs {} = int literal

    // TODO: IMPORTANT!!!
    //   We current do not have clone method for Absyn instances!!!
    //   So we do not support conditional set!!!
    absyn::Expr* cd = lt->getCond();
    if (cd != NULL) {
      error(cd->line, cd->col, "For Evidence Set, We DO NOT support condition for Cond Set now.");
      return;
    }
    lt->setCond(NULL);
    // TODO: IMPORTANT!!!
    //   due to lack of clone method, 
    //      we only support list set containing VarRef
    std::vector<absyn::Symbol> sym;
    for (size_t k = 0; k < rt->size(); ++k) {
      auto ref = dynamic_cast<absyn::VarRef*>(rt->get(k));
      if (ref == NULL) {
        error(rt->line, rt->col, "For Evidence Set, We Only Support VarRef in the List Set.");
        return;
      }
      sym.push_back(ref->getVar());
    }

    // Modify BLOG Program now!
    absyn::VarDecl var = lt->getVar();
    ev->setLeft(new absyn::CardinalityExpr(line, col, lt));
    ev->setRight(new absyn::IntLiteral(line, col, rt->size()));
    // :::=> randon <element> ~ UniformChoice({T t: t != prev})
    for (size_t k = 0; k < sym.size(); ++k) {
      auto dist = new absyn::DistrExpr(line, col, absyn::Symbol("UniformChoice"));
      absyn::Expr* root = NULL;
      for (size_t p = 0; p < k; ++p) {
        auto cur = new absyn::OpExpr(line, col, absyn::AbsynConstant::NEQ,
          new absyn::VarRef(line, col, var.getVar()), new absyn::VarRef(line, col, sym[p]));
        if (root == NULL) root = cur;
        else
          root = new absyn::OpExpr(line, col, absyn::AbsynConstant::AND, root, cur);
      }
      auto arg = new absyn::CondSet(line, col, var, root);
      dist->add(arg);
      auto func = new absyn::FuncDecl(line, col, true, var.getTyp(), sym[k], dist);
      all.push_back(func);
    }
  }
}

void Preprocessor::error(int line, int col, std::string info) {
  errorMsg.error(line, col, info);
}

void Preprocessor::warning(int line, int col, std::string info) {
  errorMsg.warning(line, col, info);
}

bool Preprocessor::Okay() {
  return errorMsg.Okay();
}

absyn::BlogProgram* Preprocessor::getProg() {
  isResultUsed = true;
  return blogProg;
}

}
} /* namespace swift */
