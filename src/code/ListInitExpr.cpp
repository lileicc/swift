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

ListInitExpr::ListInitExpr(std::vector<Expr*> subExprs) :
    Expr(subExprs) {
}

ListInitExpr::~ListInitExpr() {
}

void ListInitExpr::print(printer::Printer* prt) {
  prt->print(this);
}

}
}
