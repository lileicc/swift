/*
 * ForStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Expr.h"
#include "CompoundStmt.h"

namespace swift {
namespace code {

class ForStmt: public swift::code::Stmt {
public:
  ForStmt();
  ~ForStmt();

  void setInit(Stmt* it);
  Stmt* getInit();
  void setCond(Expr* cd);
  Expr* getCond();
  void setStep(Expr* st);
  Expr* getStep();
  void setRange(bool r);
  bool isRange() const;
  void addStmt(Stmt* st);
  CompoundStmt& getBody();

  // For Printer
  void print(printer::CPPPrinter* prt);

private:
  CompoundStmt body;
  Stmt* init;
  Expr* cond;
  Expr* step;
  bool range;
  /*
    if range == true
      then this if statment contains a C++11 range expression
    e.g.
    for(auto i : args)
    init = new BinaryOperator(new VarRef("i"), new VarRef("args"), ':')
    cond = step = NULL
    isRange = true
  */
};

} /* namespace code */
} /* namespace swift */
