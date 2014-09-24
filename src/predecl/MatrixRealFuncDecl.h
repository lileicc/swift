/*
  Interface for all matrix functions whose return value is Real
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixRealFuncDecl: public swift::predecl::PreDecl {
public:
  MatrixRealFuncDecl(std::string name);
  virtual ~MatrixRealFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
