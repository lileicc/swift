#pragma once
#include "ConstSymbol.h"

namespace swift { namespace ir {

class BoolLiteral :
  public swift::ir::ConstSymbol {
public:
  BoolLiteral(bool v = false);
  virtual ~BoolLiteral();

  bool getValue() const ;

private:
  bool value;
};

}
}