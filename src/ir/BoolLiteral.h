#pragma once
#include "ConstSymbol.h"

namespace swift {
namespace ir {

class BoolLiteral: public swift::ir::ConstSymbol {
public:
  BoolLiteral(bool v = false);
  virtual ~BoolLiteral();

  bool getValue() const;

  virtual std::string toString();
  void print(FILE* file, int indent) const;

private:
  bool value;
};

}
}
