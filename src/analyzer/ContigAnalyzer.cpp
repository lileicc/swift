/*
 * ContigAnalyzer.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: yiwu
 */

#include "ContigAnalyzer.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>
#include <set>

#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

ContigAnalyzer::ContigAnalyzer(std::shared_ptr<ir::BlogModel> _model)
  : Analyzer(_model) {
}

std::vector<std::shared_ptr<ir::Expr>>& ContigAnalyzer::getContig(std::shared_ptr<ir::Clause> c) {
  return contigVarList[c];
}

std::vector<std::shared_ptr<ir::Expr>>& ContigAnalyzer::getChild(std::shared_ptr<ir::Clause> c) {
  return childVarList[c];
}

std::vector<std::shared_ptr<ir::Expr>>& ContigAnalyzer::getReferredVar(std::shared_ptr<ir::Clause> c) {
  return referVarList[c];
}

std::vector<std::shared_ptr<ir::FuncDefn>>& ContigAnalyzer::getReferredFunc(std::shared_ptr<ir::Clause> c) {
  return referFuncList[c];
}

std::vector<std::shared_ptr<ir::NumberStmt>>& ContigAnalyzer::getReferredNumberVar(std::shared_ptr<ir::Clause> c) {
  return referNumVarList[c];
}

bool ContigAnalyzer::hasSub(std::shared_ptr<ir::Clause> c) {
  return hasSubTerm[c];
}

////////////////////////////////////////////////////
///              Util Functions
////////////////////////////////////////////////////

void ContigAnalyzer::util_set_union(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
  std::map<std::string, std::shared_ptr<ir::Expr>>&B) {
  for (auto&b : B) {
    if (A.count(b.first) == 0) {
      A.insert(b);
    }
  }
}

void ContigAnalyzer::util_set_intersect(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
  std::map<std::string, std::shared_ptr<ir::Expr>>&B) {
  std::map<std::string, std::shared_ptr<ir::Expr>>::iterator it;
  for (it = A.begin(); it != A.end(); ) {
    if (B.count(it->first) == 0) {
      A.erase(it ++);
    } else
      it ++;
  }
}

void ContigAnalyzer::util_set_minus(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
  std::map<std::string, std::shared_ptr<ir::Expr>>&B) {
  std::map<std::string, std::shared_ptr<ir::Expr>>::iterator it;
  for (it = A.begin(); it != A.end();) {
    if (B.count(it->first) > 0) {
      A.erase(it++);
    }
    else
      it++;
  }
}

bool ContigAnalyzer::util_set_same(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
  std::map<std::string, std::shared_ptr<ir::Expr>>&B) {
  if (A.size() != B.size()) return false;
  for (auto&a : A) {
    if (B.count(a.first) == 0) return false;
  }
  return true;
}

////////////////// END of Utils ////////////////////

void ContigAnalyzer::parse_expr(std::shared_ptr<ir::Expr> expr, bool is_restricted) {
  auto card = std::dynamic_pointer_cast<ir::CardExpr>(expr);
  if (card != nullptr) {
    auto st = std::dynamic_pointer_cast<ir::CondSet>(card->getBody());
    if (st == nullptr) return ; // Should not reach this!
    const ir::NameTy* ty = dynamic_cast<const ir::NameTy*>(st->getVar()->getTyp());
    if (ty == NULL || ty->getRefer()->getNumberStmtSize() == 0) return ; // Not an Open Type

    // create an empty card expression referring to the number variable
    auto trans_st = std::make_shared<ir::CondSet>(
      std::make_shared<ir::VarDecl>(ty, ""), nullptr);
    auto tynum = std::make_shared<ir::CardExpr>();
    tynum->setBody(trans_st);

    std::string str = tynum->toString();
    (*cur_referredVar)[str] = tynum;
    (*cur_condVar)[str] = tynum;
    if (is_restricted) {
      (*cur_restrictVar)[str] = tynum;
    }

    if (st->getCond() != nullptr) {
      // TODO: to handle general condition set
      errMsg.warning(-1, -1, "[Contingency Analyzer] : [Condition Set] might not be correctly handled now!");
    }

    return ;
  }

  auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(expr);
  if (fun != nullptr && fun->getKind() == ir::IRConstant::RANDOM) {
    std::string str = expr->toString();
    (*cur_referredVar)[str] = expr;
    (*cur_condVar)[str] = expr;
    if (is_restricted) {
      (*cur_restrictVar)[str] = expr;
    }
    is_restricted = true;
  }

  for (auto& e : expr->getArgs()) {
    parse_expr(e, is_restricted);
  }
}

void ContigAnalyzer::process_fetch(std::shared_ptr<ir::Clause> cls, bool restricted_flag) {
  if (referredVar.count(cls) > 0) return ;

  auto backup_condVar = cur_condVar;
  auto backup_restrictVar = cur_restrictVar;
  auto backup_referredVar = cur_referredVar;

  cur_condVar = &condVar[cls];
  cur_restrictVar = &restrictVar[cls];
  cur_referredVar = &referredVar[cls];

  auto expr = std::dynamic_pointer_cast<ir::Expr>(cls);
  if (expr != nullptr) {
    parse_expr(expr, restricted_flag); // This expression represents the distribution! Flag should be * TRUE *

    cur_condVar = backup_condVar; cur_restrictVar = backup_restrictVar; cur_referredVar = backup_referredVar;
    return ;
  }

  auto ifst = std::dynamic_pointer_cast<ir::IfThen>(cls);
  auto brch = std::dynamic_pointer_cast<ir::Branch>(cls);
 
  if (ifst == nullptr && brch == nullptr) {
    // Should Never Reach Here
    assert(false);
  }

  std::vector<std::shared_ptr<ir::Clause>> branches;

  if (ifst != nullptr) {
    parse_expr(ifst->getCond(), false);
    if (ifst->getThen() != nullptr) branches.push_back(ifst->getThen());
    if (ifst->getElse() != nullptr) branches.push_back(ifst->getElse());
  }
  if (brch != nullptr) {
    parse_expr(brch->getVar(), false);
    for (auto&b : brch->getBranches()) 
      branches.push_back(b);
  }

  // process all branches
  std::map<std::string, std::shared_ptr<ir::Expr>> join_cond, join_restrict, join_referred;

  bool same_reference = true;

  for (size_t i = 0; i < branches.size(); ++i) {
    auto b = branches[i];
    process_fetch(b);

    if (i == 0) {
      join_cond = condVar[b];
      join_restrict = restrictVar[b];
      join_referred = referredVar[b];
    }
    else {
      util_set_intersect(join_cond, condVar[b]);
      util_set_intersect(join_restrict, restrictVar[b]);

      if (!util_set_same(join_referred, referredVar[b])) same_reference = false;
      util_set_union(join_referred, referredVar[b]);
    }
  }

  util_set_union(*cur_referredVar, join_referred); // update referredVar

  if (!same_reference) {
    util_set_union(*cur_restrictVar, *cur_condVar); // all the condition var are switching var as well
  }

  util_set_union(*cur_restrictVar, join_restrict);
  util_set_union(*cur_condVar, join_cond);

  for (auto&b : branches) {
    util_set_minus(condVar[b], *cur_condVar);
    util_set_minus(restrictVar[b], *cur_restrictVar);
  }

  cur_condVar = backup_condVar; cur_restrictVar = backup_restrictVar; cur_referredVar = backup_referredVar;
  return ;
}

bool ContigAnalyzer::generate_conting(std::shared_ptr<ir::Clause> cls) {
  if (hasSubTerm.count(cls) > 0) return hasSubTerm[cls];

  bool &sub = hasSubTerm[cls]; 
  sub = false;
  bool ret = false;

  auto& cur_contig = contigVarList[cls];
  auto& cur_child = childVarList[cls];

  auto& cur_cond = condVar[cls];
  auto& cur_restrict = restrictVar[cls];

  std::vector<std::string> str_child;
  std::vector<std::string> str_contig;

  for (auto&r : cur_restrict) {
    if (stack_contig.count(r.first) == 0) {
      ret=true;
      stack_contig.insert(r.first);
      str_contig.push_back(r.first);
      cur_contig.push_back(r.second);
    }
  }
  for (auto&c : cur_cond) {
    if (stack_child.count(c.first) == 0) {
      ret=true;
      stack_child.insert(c.first);
      str_child.push_back(c.first);
      cur_child.push_back(c.second);
    }
  }

  auto fun = std::dynamic_pointer_cast<ir::IfThen>(cls);
  if (fun != nullptr) {
    if (fun->getThen() != nullptr)
      sub |= generate_conting(fun->getThen());
    if (fun->getElse() != nullptr)
      sub |= generate_conting(fun->getElse());
  }

  auto brch = std::dynamic_pointer_cast<ir::Branch>(cls);
  if (brch != nullptr) {
    for (auto&b : brch->getBranches()) {
      sub |= generate_conting(b);
    }
  }

  for (auto& c : str_contig) {
    stack_contig.erase(c);
  }

  for (auto& c : str_child) {
    stack_child.erase(c);
  }

  // process referVar and referFunc
  auto& var_ref = referredVar[cls];
  auto& cur_var = referVarList[cls];
  auto& cur_func = referFuncList[cls];
  auto& cur_numst = referNumVarList[cls];
  std::set<std::shared_ptr<ir::FuncDefn>> func_hash;
  std::set<std::shared_ptr<ir::NumberStmt>> numst_hash;
  for (auto&v : var_ref) {
    auto expr = v.second;
    cur_var.push_back(expr);
    // check random var
    auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(expr);
    if (fun != nullptr && fun->getKind()==ir::IRConstant::RANDOM) {
      if (func_hash.count(fun->getRefer()) == 0) {
        func_hash.insert(fun->getRefer());
        cur_func.push_back(fun->getRefer());
      }
    }
    // check number statement
    auto num = std::dynamic_pointer_cast<ir::CardExpr>(expr);
    if (num != nullptr) {
      auto st = std::dynamic_pointer_cast<ir::CondSet>(num->getBody());
      if (st != nullptr) {
        auto ty = dynamic_cast<const ir::NameTy*>(st->getVar()->getTyp());
        if (ty != NULL && ty->getRefer()->getNumberStmtSize() > 0) {
          auto& allnumst = ty->getRefer()->getAllNumberStmt();
          for (auto& n : allnumst) {
            if (numst_hash.count(n) == 0) {
              numst_hash.insert(n);
              cur_numst.push_back(n);
            }
          }
        }
      }
    }
    // Else: do nothing
  }
  
  return ret || sub;
}

bool ContigAnalyzer::process() {
  condVar.clear();
  restrictVar.clear();
  referredVar.clear();
  contigVarList.clear();
  childVarList.clear();
  referVarList.clear();
  referFuncList.clear();
  referNumVarList.clear();
  hasSubTerm.clear();

  // Number Statement
  for (auto& ty : model->getTypes()) {
    if (ty->getOriginSize() > 0) {
      // TODO: Origin Function
      // Origin Function Requires Block Sampling and Dynamic Dependency maintainance
      errMsg.error(-1, -1, "[Contigency Analyzer] : < Origin Function > is currently not supported!");
      continue;
    }
    
    for (auto&stmt : ty->getAllNumberStmt()) {
      if (stmt->getAllVars().size() > 0) continue; // Currently do not support origin functions

      process_fetch(stmt->getBody());

      stack_child.clear();
      stack_contig.clear();
      generate_conting(stmt->getBody());
    }
  }

  // Random Variables
  for (auto&fun : model->getRandFuncs()) {
    process_fetch(fun->getBody());

    stack_child.clear();
    stack_contig.clear();
    generate_conting(fun->getBody());
  }

  // Evidences
  for (auto&evi : model->getEvidences()) {
    process_fetch(evi->getLeft(), false);

    stack_child.clear();
    stack_contig.clear();
    generate_conting(evi->getLeft());
  }

  if (!errMsg.Okay()) {
    contigVarList.clear();
    childVarList.clear();
    referVarList.clear();
    referFuncList.clear();
    referNumVarList.clear();
    return false;
  }

  return true;
}

}
} /* namespace swift */
