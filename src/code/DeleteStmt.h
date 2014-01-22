/*
 * DeleteStmt.h
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "Identifier.h"

namespace swift {
namespace code {

class DeleteStmt: public swift::code::Stmt {
public:
  DeleteStmt(Identifier* var, bool arrayDel=false);
  ~DeleteStmt();
  bool isArray() const;
  Identifier* getVar();
  void print(printer::Printer* prt);
private:
  Identifier* var;
  bool arrayDel;
};

} /* namespace code */
} /* namespace swift */
