/*
 * Analyzer.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: leili
 */

#include "Analyser.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>
#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

Analyzer::Analyzer() {
}

Analyzer::~Analyzer() {
}

void Analyzer::processRandom(ir::BlogModel* model) {
  // Check Number Statement
  for (auto ty : model->getTypes())
    for (auto ns: ty->getAllNumberStmt())
      processRandom(ns->getBody());
  // Check Randomness of Random Function
  for (auto fun : model->getRandFuncs())
    processRandom(fun->getBody());
  // Check Randomness of Query
  for (auto q : model->getQueries())
    processRandom(q->getVar());
}

bool Analyzer::processRandom(std::shared_ptr<ir::Clause> term) {
  auto brch = std::dynamic_pointer_cast<ir::Branch>(term);
  if (brch != nullptr)
    return processRandom(brch);
  auto ifth = std::dynamic_pointer_cast<ir::IfThen>(term);
  if (ifth != nullptr)
    return processRandom(ifth);
  auto expr = std::dynamic_pointer_cast<ir::Expr>(term);
  if (expr != nullptr)
    return processRandom(expr);
  return false;
}

bool Analyzer::processRandom(std::shared_ptr<ir::Branch> term) {
  bool ret = false;
  for (auto b : term->getBranches())
    ret |= processRandom(b);
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::IfThen> term) {
  bool ret = false;
  ret |= processRandom(term->getCond());
  if (term->getThen() != nullptr)
    ret |= processRandom(term->getThen());
  if (term->getElse() != nullptr)
    ret |= processRandom(term->getElse());
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::Expr> term) {
  auto arr = std::dynamic_pointer_cast<ir::ArrayExpr>(term);
  if (arr != nullptr)
    return processRandom(arr);
  auto card = std::dynamic_pointer_cast<ir::CardExpr>(term);
  if (card != nullptr)
    return processRandom(card);
  auto st = std::dynamic_pointer_cast<ir::SetExpr>(term);
  if (st != nullptr)
    return processRandom(st);
  auto sym = std::dynamic_pointer_cast<ir::ConstSymbol>(term);
  if (sym != nullptr)
    return processRandom(sym);
  auto distr = std::dynamic_pointer_cast<ir::Distribution>(term);
  if (distr != nullptr)
    return processRandom(distr);
  auto cll = std::dynamic_pointer_cast<ir::FunctionCall>(term);
  if (cll != nullptr)
    return processRandom(cll);
  auto mp = std::dynamic_pointer_cast<ir::MapExpr>(term);
  if (mp != nullptr)
    return processRandom(mp);
  auto opr = std::dynamic_pointer_cast<ir::OprExpr>(term);
  if (opr != nullptr)
    return processRandom(opr);
  auto orig = std::dynamic_pointer_cast<ir::OriginRefer>(term);
  if (orig != nullptr)
    return processRandom(orig);
  auto qnt = std::dynamic_pointer_cast<ir::QuantForm>(term);
  if (qnt != nullptr)
    return processRandom(qnt);
  auto var = std::dynamic_pointer_cast<ir::VarRefer>(term);
  if (var != nullptr)
    return processRandom(var);
  return false;
}

bool Analyzer::processRandom(std::shared_ptr<ir::ArrayExpr> term) {
  bool ret=false;
  for (auto a : term->getArgs())
    ret |= processRandom(a);
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::CardExpr> term) {
  // TODO: To do Replacement Here!!! i.e. #{a,b,c}
  term->setRandom(processRandom(term->getBody()));
  return term->isRandom();
}

bool Analyzer::processRandom(std::shared_ptr<ir::CondSet> term) {
  // TODO: Check whether cond() is always false
  if(term->getCond() != nullptr)
    processRandom(term->getCond());
  term->setRandom(true);
  return true;
}

bool Analyzer::processRandom(std::shared_ptr<ir::ConstSymbol> term) {
  term->setRandom(false);
  return false;
}

bool Analyzer::processRandom(std::shared_ptr<ir::Distribution> term) {
  for (auto a : term->getArgs())
    processRandom(a);
  term->setRandom(true);
  return true;
}

bool Analyzer::processRandom(std::shared_ptr<ir::FunctionCall> term) {
  // TODO: Note that we might change the randomness of a defined function
  //    When should we confirm the randomness of each defined function????
  term->setRandom(term->getRefer()->isRand());
  return term->isRandom();
}

bool Analyzer::processRandom(std::shared_ptr<ir::ListSet> term) {
  bool ret=false;
  for (auto a : term->getArgs())
    ret |= processRandom(a);
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::MapExpr> term) {
  bool ret = false;
  for (auto a: term->getArgs())
    ret |= processRandom(a);
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::OprExpr> term) {
  // TODO: To Do Replacement Here!!! i.e. 1 + 2
  bool ret=false;
  for (auto a : term->getArgs())
    ret |= processRandom(a);
  term->setRandom(ret);
  return ret;
}

bool Analyzer::processRandom(std::shared_ptr<ir::OriginRefer> term) {
  processRandom(term->getVar());
  term->setRandom(true);
  return true;
}

bool Analyzer::processRandom(std::shared_ptr<ir::QuantForm> term) {
  if(term->getCond() != nullptr) 
    processRandom(term->getCond());
  // TODO: to do replacement
  term->setRandom(true);
  return true;
}

bool Analyzer::processRandom(std::shared_ptr<ir::SetExpr> term) {
  auto lst = std::dynamic_pointer_cast<ir::ListSet>(term);
  if (lst != nullptr) 
    return processRandom(lst);
  auto cnd = std::dynamic_pointer_cast<ir::CondSet>(term);
  if (cnd != nullptr)
    return processRandom(cnd);
  return false;
}

bool Analyzer::processRandom(std::shared_ptr<ir::VarRefer> term) {
  term->setRandom(false);
  return false;
}

}
} /* namespace swift */
