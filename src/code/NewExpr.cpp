/*
 * NewExpr.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: yiwu
 */
#include <vector>
#include "NewExpr.h"

namespace swift {
namespace code {

NewExpr::NewExpr(Expr* expr) :
    Expr(std::vector<Expr*>( { expr })) {
}

NewExpr::~NewExpr() {
}

Expr* NewExpr::getExpr() const {
  return args[0];
}

void NewExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
