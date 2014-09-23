/*
  Interface for matrix stacking functions which takes in a list of matrix
  and returns a matrix
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixStackFuncDecl: public swift::predecl::PreDecl {
public:
  MatrixStackFuncDecl(std::string name);
  virtual ~MatrixStackFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
