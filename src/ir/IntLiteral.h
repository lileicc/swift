#pragma once

#include "ConstSymbol.h"

namespace swift {
namespace ir {

class IntLiteral: public swift::ir::ConstSymbol {
public:
  IntLiteral(int v = 0);
  virtual ~IntLiteral();

  int getValue() const;

  virtual std::string toString();
  void print(FILE* file, int indent) const;
private:
  int value;
};

}
}
