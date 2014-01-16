//
//  ListInitExpr.h
//  swift-project
//
//  Created by Lei Li on 1/16/14.
//
//

#pragma once

#include <vector>
#include <string>
#include "Expr.h"

namespace swift {
namespace code {

class ListInitExpr: public Expr {
public:
  ListInitExpr(const std::vector<Expr*>& subExprs);
  ~ListInitExpr();
  std::vector<Expr*>& getSubExprs();
  // For Printer
  void print(printer::Printer* prt);
private:
  std::vector<Expr*> subExprs;
};

} /* namespace code */
} /* namespace swift */
