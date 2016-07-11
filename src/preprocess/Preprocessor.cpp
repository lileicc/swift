/*
 * Preprocessor.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: yiwu
 */

#include "Preprocessor.h"

#include "../absyn/ArrayExpr.h"

#include <cassert>
#include <memory>
#include <utility>

namespace swift {
namespace preprocess {

Preprocessor::Preprocessor() :
    errorMsg(stderr), blogProg(NULL) {
}

Preprocessor::~Preprocessor() {
}

void Preprocessor::process(absyn::BlogProgram* prog) {
  blogProg = prog;
  // Process Set Evidence
  processSetEvidence(blogProg);

  // Process Macros used in the expressions
  processMacro(blogProg);
}

void Preprocessor::processSetEvidence(absyn::BlogProgram*& prog) {
  // Note: It is reference here! We have to modify the BLOG program!
  std::vector<absyn::Stmt*>& all = prog->getAllRef();
  for (size_t i = 0; i < all.size(); ++i) {
    absyn::Evidence* ev = dynamic_cast<absyn::Evidence*>(all[i]);
    if (ev == NULL) continue;
    absyn::SetExpr* lt = dynamic_cast<absyn::SetExpr*>(ev->getLeft());
    absyn::ListSet* rt = dynamic_cast<absyn::ListSet*>(ev->getRight());
    if (lt == NULL || rt == NULL) continue;
    if (dynamic_cast<absyn::ListSet*>(lt)!= NULL) continue;
    int line = rt->line, col = rt->col;
    absyn::CondSet* lcs = dynamic_cast<absyn::CondSet*>(lt);
    absyn::TupleSetExpr* lts = dynamic_cast<absyn::TupleSetExpr*>(lt);
    std::vector<absyn::Expr*> lfunc;
    if (lts != NULL) lfunc = lts->getExps();
    absyn::Expr* lcond = (lts != NULL ? lts->getCond() : lcs->getCond());
    if (lts != NULL && lts->getVarDecls().size() != 1) {
      //TODO: to support tupleset with multiple vars
      error(ev->line, ev->col, "For Set Evidence, we DO NOT support TupleSetExpr with Mutiple Variables!");
      return ;
    }

    if (ev->getVarDecls().size() > 0) {
      //TODO: to support set evidence with for-loop
      error(ev->line, ev->col, "For Set Evidence, we DO NOT support for-loop now!");
      return;
    }

    absyn::VarDecl lvar(lts != NULL ? lts->getVarDecl(0) : lcs->getVar());
    // Set Evidence: obs {CondSet} = {ListSet}

    absyn::Expr* cd = lcond;
    if (cd != NULL) {
      // We DO support condition now, but a warning will be printer
      // TODO: use UniformChoiceK to better support condition
      warning(cd->line, cd->col, "For Evidence Set, condition on the set expression is not recommended!");
    }

    // TODO: IMPORTANT!!!
    //   due to lack of clone method, 
    //      we only support list set containing VarRef (FuncApp with no arguments)
    std::vector<absyn::Symbol> sym;
    for (size_t k = 0; k < rt->size(); ++k) {
      auto ref = dynamic_cast<absyn::FuncApp*>(rt->get(k));
      if (ref == NULL || ref->size() > 0) {
        error(rt->line, rt->col, "For Evidence Set, We Only Support VarRef (FuncApp with no arguments) in the List Set (right hand side of the evidence).");
        return;
      }
      sym.push_back(ref->getFuncName());
    }
    // For the same reason, we do not support general expression in TupleSetExpr
    if (lfunc.size() != 1 || dynamic_cast<absyn::FuncApp*>(lfunc[0]) == NULL || (dynamic_cast<absyn::FuncApp*>(lfunc[0])->size() > 0)
      || (dynamic_cast<absyn::FuncApp*>(lfunc[0]))->getFuncName().getValue() != lvar.getVar().getValue()) {
      error(cd->line, cd->col, "For Evidence Set, We DO NOT general expression in TupleSetExpr (the left hand side of the evidence).");
      return;
    }

    // Modify BLOG Program now!
    // :::=> obs {} = int literal
    absyn::VarDecl var = lvar;
    ev->setLeft(new absyn::CardinalityExpr(line, col, lt));
    ev->setRight(new absyn::IntLiteral(line, col, rt->size()));
    // :::=> randon <element> ~ UniformChoice({T t: t != prev})
    for (size_t k = 0; k < sym.size(); ++k) {
      auto dist = new absyn::FuncApp(line, col, absyn::Symbol("UniformChoice"));
      absyn::Expr* root = (lcond != NULL ? lcond->clone() : NULL);
      for (size_t p = 0; p < k; ++p) {
        absyn::Expr* cur = 
            new absyn::OpExpr(line, col, absyn::AbsynConstant::NEQ,
            new absyn::FuncApp(line, col, var.getVar()), new absyn::FuncApp(line, col, sym[p]));
        if (root == NULL) root = cur;
        else
          root = new absyn::OpExpr(line, col, absyn::AbsynConstant::AND, root->clone(), cur);
      }
      auto arg = new absyn::CondSet(line, col, var, root);
      dist->add(arg);
      auto ucfunc = new absyn::FuncDecl(line, col, true, var.getTyp(), sym[k], dist);
      all.push_back(ucfunc);
    }

    // Do the Pointer Clearance
    delete rt;
  }
}

std::vector<absyn::Expr*> Preprocessor::parse_macro_EXPAND(absyn::FuncApp* fun) {
  assert(fun->getFuncName().getValue() == "EXPAND");
  std::vector<absyn::Expr*> ret;
  if (fun->size() != 3) {
    error(fun->line, fun->col, "error usage for macro <EXPAND>! correct syntax: EXPAND(expr, a, b) where a and b must be non-negative FIXED integers and a <= b!");
    return ret;
  }
  auto& args = fun->getAllExpr();
  auto expr = args[0];
  auto a = dynamic_cast<absyn::IntLiteral*>(args[1]);
  auto b = dynamic_cast<absyn::IntLiteral*>(args[2]);
  if (expr == NULL || a == NULL || b == NULL
      || a->getValue() > b->getValue()
      || a->getValue() < 0) {
    error(fun->line, fun->col, "error usage for macro <EXPAND>! correct syntax: EXPAND(expr, a, b) where a and b must be non-negative FIXED integers and a <= b!");
    return ret;
  }
  int v_a = a->getValue(), v_b = b->getValue();
  for (int i = v_a; i <= v_b; ++i) {
    ret.push_back(new absyn::OpExpr(fun->line,fun->col,
      absyn::AbsynConstant::SUB,
      expr->clone(),
      new absyn::IntLiteral(fun->line, fun->col, i)));
  }
  return ret;
}

absyn::Expr* Preprocessor::parse_expr(absyn::Expr* expr) {
  if (expr == NULL) return NULL;
  auto& args = expr->getAllExpr();

  auto fun = dynamic_cast<absyn::FuncApp*>(expr);
  auto lstset = dynamic_cast<absyn::ListSet*>(expr);
  auto arr = dynamic_cast<absyn::ArrayExpr*>(expr);
  if (fun != NULL || lstset != NULL || arr != NULL) {
    // Check Macro: EXPAND, which locates in a restricted environment
    size_t ptr = 0;
    for (; ptr < args.size(); ++ ptr) {
      auto subfun = dynamic_cast<absyn::FuncApp*>(args[ptr]);
      if (subfun != NULL && subfun->getFuncName().getValue() == "EXPAND") {
        auto ret = parse_macro_EXPAND(subfun);
        if (ret.size() == 0) continue; // error
        delete args[ptr];
        args.erase(args.begin() + ptr);
        args.insert(args.begin() + ptr, ret.begin(), ret.end());
        -- ptr; // make sure that ptr keeps in the same position
        continue;
      }
    }
  }

  for (size_t i = 0; i < args.size(); ++i) {
    absyn::Expr* ret = NULL;
    ret = parse_expr(args[i]);
    if (ret != NULL) args[i] = ret;
  }

  if (arr != NULL) {
    // ensure <dim> field in ArrayExpr
    int base_dim = -1;
    absyn::ArrayExpr* sub;
    bool ok=true;
    for (size_t i = 0; i < arr->size(); i++) {
      sub = dynamic_cast<absyn::ArrayExpr*>(arr->get(i));
      if (sub != NULL) {
        if (base_dim < 0) base_dim = sub->getDim();
        else
        if (base_dim != sub->getDim()) {
          ok = false;
          if (sub->getDim() > base_dim) base_dim = sub->getDim();
        }
      }
      else {
        if (base_dim < 0) base_dim = 0;
        else 
          if (base_dim != 0) ok=false;
      }
    }
    if (!ok) {
      error(arr->line, arr->col,
        "Illegal <ArrayExpr>: Every element in the array should have the same dimension.");
    }

    if (base_dim < 0) base_dim = 0;
    if (arr->getDim() != base_dim + 1) {
      arr->setDim(base_dim + 1);
    }
  }

  return NULL;
}

void Preprocessor::processMacro(absyn::BlogProgram*& prog) {
  for (auto& st : prog->getAll()) {
    absyn::Expr* ret = NULL;
    auto fun = dynamic_cast<absyn::FuncDecl*>(st);
    if (fun != NULL) {
      ret = parse_expr(fun->getExpr());
      if (ret != NULL) fun->getExpr() = ret;
    }
    auto num = dynamic_cast<absyn::NumStDecl*>(st);
    if (num != NULL) {
      ret = parse_expr(num->getExpr());
      if (ret != NULL) num->getExpr() = ret;
    }
    auto query = dynamic_cast<absyn::Query*>(st);
    if (query != NULL) {
      ret = parse_expr(query->getExpr());
      if (ret != NULL) query->getExpr() = ret;
    }
    auto evi = dynamic_cast<absyn::Evidence*>(st);
    if (evi != NULL) {
      ret = parse_expr(evi->getLeft());
      if (ret != NULL) evi->setLeft(ret);
      ret = parse_expr(evi->getRight());
      if (ret != NULL) evi->setRight(ret);
      if (evi->getCond() != NULL) {
        ret = parse_expr(evi->getCond());
        if (ret != NULL) evi->setCond(ret);
      }
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
  return blogProg;
}

}
} /* namespace swift */
