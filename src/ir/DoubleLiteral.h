#pragma once
#include "ConstSymbol.h"

namespace swift {
namespace ir {

class DoubleLiteral: public swift::ir::ConstSymbol {
public:
  DoubleLiteral(double v = 0);
  virtual ~DoubleLiteral();

  double getValue() const;

  virtual std::string toString();
  void print(FILE* file, int indent) const;

private:
  double value;
};

}
}
