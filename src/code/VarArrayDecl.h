/*
 * VarArrayDecl.h
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#pragma once

#include <vector>
#include "VarDecl.h"

namespace swift {
namespace code {

class VarArrayDecl: public swift::code::VarDecl {
public:
  VarArrayDecl(DeclContext * context, std::string id, Type ty,
      std::vector<Expr*> arr = std::vector<Expr*>(), Expr* value = nullptr);
  virtual ~VarArrayDecl();

  const std::vector<Expr*>& getArr() const;
  // For Printer
  virtual void print(printer::Printer* prt);
protected:
  std::vector<Expr*> arr;
};

} /* namespace code */
} /* namespace swift */
