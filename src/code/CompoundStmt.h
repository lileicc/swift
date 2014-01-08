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
  size_t size() const;
  Stmt* get(int k) const;
  const std::vector<Stmt*>& getAll() const;

  // For Printer
  void print(printer::Printer* prt);

private:
  std::vector<Stmt* > body;
};

} /* namespace code */
} /* namespace swift */
