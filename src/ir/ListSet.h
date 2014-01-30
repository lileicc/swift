#pragma once
#include "SetExpr.h"

namespace swift {
namespace ir {

class ListSet: public swift::ir::SetExpr {
public:
  ListSet();
  virtual ~ListSet();
  void print(FILE* file, int indent) const;
};

}
}
