/*
 * CompoundStmt.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include <vector>
#include "Stmt.h"

namespace swift {
namespace code {

class CompoundStmt: public swift::code::Stmt {
public:
  CompoundStmt();
  ~CompoundStmt();
  void addStmt(Stmt* st);

private:
  std::vector<Stmt* > body;
};

} /* namespace code */
} /* namespace swift */
