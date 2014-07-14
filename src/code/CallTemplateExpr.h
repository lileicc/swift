/*
 * CallTemplateExpr.h
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#pragma once
#include "CallExpr.h"

namespace swift {
namespace code {

class CallTemplateExpr: public CallExpr {
public:
  CallTemplateExpr(Expr* fn, std::vector<Expr*> args = std::vector<Expr *>(), std::vector<Expr*> tempArgs = std::vector<Expr*>());
  ~CallTemplateExpr();

  static CallTemplateExpr* createMethodCall(std::string varname, std::string methodname,
      std::vector<Expr*> args = std::vector<Expr *>(), std::vector<Expr*> tempArgs = std::vector<Expr*>());
  // For Printer
  void print(printer::Printer* prt);

  const std::vector<Expr*>& getTempArgs() const;

protected:
  std::vector<Expr*> tempArgs;
};

} /* namespace code */
} /* namespace swift */
