//
//  ListInitExpr.cpp
//  swift-project
//
//  Created by Lei Li on 1/16/14.
//
//

#include "ListInitExpr.h"

namespace swift {
namespace code {

ListInitExpr::ListInitExpr(const std::vector<Expr*>& subExprs) :
    subExprs(subExprs) {
}

ListInitExpr::~ListInitExpr() {
  for (auto x : subExprs) {
    delete x;
  }
}

std::vector<Expr*>& ListInitExpr::getSubExprs() {
  return subExprs;
}

void ListInitExpr::print(printer::Printer* prt) {
  prt->print(this);
}

}
}
