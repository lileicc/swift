/*
 * TemplateExpr.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: yiwu
 */

#include "TemplateExpr.h"
#include "Identifier.h"
#include "BinaryOperator.h"

namespace swift {
namespace code {

TemplateExpr::TemplateExpr(code::Expr* var, std::vector<code::Expr*> tempArgs) :
    Expr(tempArgs), var(var){
}

TemplateExpr::~TemplateExpr() {
}

Expr* TemplateExpr::getVar() const {
  return var;
}

// For Printer
void TemplateExpr::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */

