/*
  Interface for matrix initialization functions
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixConstructFuncDecl: public swift::predecl::PreDecl {
public:
  MatrixConstructFuncDecl(std::string name);
  virtual ~MatrixConstructFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
