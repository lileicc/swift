/*
 * Analyzer.h
 *
 *  Created on: Feb 13, 2014
 *      Author: yiwu
 */

#pragma once

#include <memory>
#include "../ir/BlogModel.h"

namespace swift {
namespace analyzer {

class Analyzer {
public:
  Analyzer();
  ~Analyzer();
 
  void processRandom(ir::BlogModel* model);

private:
  // Process Random: setRandom()
  bool processRandom(std::shared_ptr<ir::Clause> term);
  bool processRandom(std::shared_ptr<ir::Branch> term);
  bool processRandom(std::shared_ptr<ir::IfThen> term);
  bool processRandom(std::shared_ptr<ir::Expr> term);
  //      Process Random: for Expr
  bool processRandom(std::shared_ptr<ir::ArrayExpr> term);
  bool processRandom(std::shared_ptr<ir::CardExpr> term);
  bool processRandom(std::shared_ptr<ir::CondSet> term);
  bool processRandom(std::shared_ptr<ir::ConstSymbol> term);
  bool processRandom(std::shared_ptr<ir::Distribution> term);
  bool processRandom(std::shared_ptr<ir::FunctionCall> term);
  bool processRandom(std::shared_ptr<ir::ListSet> term);
  bool processRandom(std::shared_ptr<ir::MapExpr> term);
  bool processRandom(std::shared_ptr<ir::OprExpr> term);
  bool processRandom(std::shared_ptr<ir::OriginRefer> term);
  bool processRandom(std::shared_ptr<ir::QuantForm> term);
  bool processRandom(std::shared_ptr<ir::SetExpr> term);
  bool processRandom(std::shared_ptr<ir::VarRefer> term);
};

}
} /* namespace swift */
