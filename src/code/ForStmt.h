/*
 * ForStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "Stmt.h"
#include "Expr.h"
#include "CompoundStmt.h"
#pragma once

namespace swift {
namespace code {

class ForStmt: public swift::code::Stmt {
public:
  ForStmt(Stmt* init, Expr* cond, Expr* step, Stmt* body=NULL);
  ~ForStmt();

  void setInit(Stmt* it);
  Stmt* getInit();
  void setCond(Expr* cd);
  Expr* getCond();
  void setStep(Expr* st);
  Expr* getStep();
  void setRange(bool r);
  bool isRange() const;
  Stmt* getBody();

  // For Printer
  void print(printer::Printer* prt);

private:
  Stmt* init;
  Expr* cond;
  Expr* step;
  Stmt* body;
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
