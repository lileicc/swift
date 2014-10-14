/*
 * TemplateExpr.h
 *
 *  Created on: Oct 13, 2014
 *      Author: yiwu
 */

#pragma once
#include "Expr.h"

namespace swift {
namespace code {

class TemplateExpr: public Expr {
public:
  TemplateExpr(Expr* var, std::vector<Expr*> tempArgs = std::vector<Expr *>());
  ~TemplateExpr();

  Expr* getVar() const ;

  // For Printer
  void print(printer::Printer* prt);

protected:
  Expr* var;
};

} /* namespace code */
} /* namespace swift */
