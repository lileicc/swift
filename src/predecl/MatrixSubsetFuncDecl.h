/*
  Interface for matrix subset functions
*/

#pragma once
#include "PreDecl.h"

namespace swift {
namespace predecl {

class MatrixSubsetFuncDecl: public swift::predecl::PreDecl {
private:
  int n_args;
public:
  MatrixSubsetFuncDecl(std::string name, int n_args);
  virtual ~MatrixSubsetFuncDecl();

  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const;
};

}
}
