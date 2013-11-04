#pragma once

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class Evidence {
public:
  Evidence(Expr* left, Expr* right);
  virtual ~Evidence();

  Expr* getLeft();
  Expr* getRight();

private:
  Expr* left;
  Expr* right;
};

}
}