/*
 * CallExpr.h
 *
 *  Created on: Nov 26, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include <string>
#include "Expr.h"


namespace swift {
namespace code {

class CallExpr: public Expr {
public:
  CallExpr(Expr* fn, std::vector<Expr*> args = std::vector<Expr *>());
  ~CallExpr();

  Expr* getFunc();
  std::vector<Expr*>& getArgs();

  static CallExpr* createMethodCall(std::string varname, std::string methodname,
      std::vector<Expr*> args = std::vector<Expr *>());
  // For Printer
  void print(printer::Printer* prt);
private:
  Expr* fn;
  std::vector<Expr*> args;
};

} /* namespace code */
} /* namespace swift */
