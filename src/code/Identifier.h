/*
 * Identifier.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include <string>
#include "Expr.h"

namespace swift {
namespace code {

class Identifier: public swift::code::Expr {
public:
  Identifier(std::string id);
  ~Identifier();

  const std::string& getId() const;

  // For Printer
  void print(printer::Printer* prt);
private:
  std::string id;
};

} /* namespace code */
} /* namespace swift */
