/*
 * DeclStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Decl.h"

namespace swift {
namespace code {

class DeclStmt: public swift::code::Stmt {
public:
  DeclStmt(Decl* dec);
  ~DeclStmt();

  Decl* getDecl();

  // For Printer
  void print(printer::Printer* prt);

private:
  Decl* dec;
};

} /* namespace code */
} /* namespace swift */
