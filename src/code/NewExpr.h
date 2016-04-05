/*
 * NewExpr.h
 *
 *  Created on: Apr 15, 2015
 *      Author: yiwu
 */

#pragma once

#include "Expr.h"

namespace swift {
namespace code {

class NewExpr: public swift::code::Expr {
public:
  NewExpr(Expr* expr);
  ~NewExpr();

  Expr* getExpr() const;

  // For Printer
  void print(printer::Printer* prt);
};

} /* namespace code */
} /* namespace swift */
