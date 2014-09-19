/*
  Interface for all matrix functions whose return value is also matrix
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixMatrixFuncDecl: public swift::predecl::PreDecl {
public:
  MatrixMatrixFuncDecl(std::string name);
  virtual ~MatrixMatrixFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
