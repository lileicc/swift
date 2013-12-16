/*
 * ForStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
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
  void setStep(Stmt* st);
  Stmt* getStep();
  void addStmt(Stmt* st);
  CompoundStmt& getBody();

  // For Printer
  void print(printer::CPPPrinter* prt);

private:
  CompoundStmt body;
  Stmt* init;
  Expr* cond;
  Stmt* step;
};

} /* namespace code */
} /* namespace swift */
