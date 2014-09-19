/*
  Interface for all math functions
   1. Real/Int -> Real
   2. Matrix -> Matrix
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MathFuncDecl: public swift::predecl::PreDecl {
public:
  MathFuncDecl(std::string name);
  virtual ~MathFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
