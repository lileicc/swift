/*
 * ContigAnalyzer.h
 *
 *  Created on: Apr 20, 2015
 *      Author: yiwu
 */

#pragma once

#include <map>
#include <memory>
#include <vector>
#include <set>
#include <string>
#include "Analyzer.h"

namespace swift {
namespace analyzer {

class ContigAnalyzer: public Analyzer{
public:
  ContigAnalyzer(std::shared_ptr<ir::BlogModel> _model = nullptr);
 
  // return true when the input model is compatible with the analyzer
  virtual bool process();

  std::vector<std::shared_ptr<ir::Expr>>& getContig(std::shared_ptr<ir::Clause> c);
  std::vector<std::shared_ptr<ir::Expr>>& getChild(std::shared_ptr<ir::Clause> c);
  bool hasSub(std::shared_ptr<ir::Clause> c);

private:
  std::map<std::shared_ptr<ir::Clause>, std::vector<std::shared_ptr<ir::Expr>>> contigVar;
  std::map<std::shared_ptr<ir::Clause>, std::vector<std::shared_ptr<ir::Expr>>> childVar;
  std::map<std::shared_ptr<ir::Clause>, bool> hasSubTerm;

  std::map<std::shared_ptr<ir::Clause>, std::map<std::string, std::shared_ptr<ir::Expr>>> condVar;
  std::map<std::shared_ptr<ir::Clause>, std::map<std::string, std::shared_ptr<ir::Expr>>> restrictVar;
  std::map<std::shared_ptr<ir::Clause>, std::map<std::string, std::shared_ptr<ir::Expr>>> referredVar;

  std::set<std::string> stack_child;
  std::set<std::string> stack_contig;

  std::map<std::string, std::shared_ptr<ir::Expr>>* cur_condVar, *cur_restrictVar, *cur_referredVar;

  void parse_expr(std::shared_ptr<ir::Expr> expr, bool is_restricted = false);

  void process_fetch(std::shared_ptr<ir::Clause> cls);

  bool generate_conting(std::shared_ptr<ir::Clause> cls);

  ///////////////////////
  //  Util Functions
  ///////////////////////
  /*
   * Set Operation: A = A U B
   */
  void util_set_union(std::map<std::string, std::shared_ptr<ir::Expr>>&A, 
    std::map<std::string, std::shared_ptr<ir::Expr>>&B);
  /*
   * Set Operation: A = A ^ B
   */
  void util_set_intersect(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
    std::map<std::string, std::shared_ptr<ir::Expr>>&B);
  /*
   * Set Operation: A = A - B
   */
  void util_set_minus(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
    std::map<std::string, std::shared_ptr<ir::Expr>>&B);
  /*
   * Set Equality
   */
  bool util_set_same(std::map<std::string, std::shared_ptr<ir::Expr>>&A,
    std::map<std::string, std::shared_ptr<ir::Expr>>&B);
};

}
} /* namespace swift */
