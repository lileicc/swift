#pragma once
#include "ConstSymbol.h"

namespace swift {
namespace ir {

class NullSymbol: public swift::ir::ConstSymbol {
public:
  NullSymbol();
  virtual ~NullSymbol();

  virtual std::string toString();
  void print(FILE* file, int indent) const;
};

}
}
