/*
  Interface for matrix initialization functions
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixInitFuncDecl: public swift::predecl::PreDecl {
public:
  MatrixInitFuncDecl(std::string name);
  virtual ~MatrixInitFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
