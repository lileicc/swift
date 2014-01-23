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
  ListInitExpr(std::vector<Expr*> subExprs);
  ~ListInitExpr();
  // For Printer
  void print(printer::Printer* prt);
};

} /* namespace code */
} /* namespace swift */
