/*
 * DeleteStmt.h
 *
 *  Created on: Jan 13, 2014
 *      Author: leili
 */

#pragma once

#include "Stmt.h"
#include "VarRef.h"

namespace swift {
namespace code {

class DeleteStmt: public swift::code::Stmt {
public:
  DeleteStmt(VarRef* var, bool arrayDel=false);
  ~DeleteStmt();
  bool isArray() const;
  const VarRef* getVar() const;
  void print(printer::Printer* prt);
private:
  VarRef* var;
  bool arrayDel;
};

} /* namespace code */
} /* namespace swift */
