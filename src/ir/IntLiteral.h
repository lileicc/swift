#pragma once

#include "ConstSymbol.h"

namespace swift { namespace ir {

class IntLiteral :
  public swift::ir::ConstSymbol {
public:
  IntLiteral(int v = 0);
  virtual ~IntLiteral();

  int getValue() const;
private:
  int value;
};

}
}