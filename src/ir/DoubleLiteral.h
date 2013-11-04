#pragma once
#include "ConstSymbol.h"

namespace swift { namespace ir {

class DoubleLiteral :
  public swift::ir::ConstSymbol {
public:
  DoubleLiteral(double v=0);
  virtual ~DoubleLiteral();

  double getValue();

private:
  double value;
};

}
}