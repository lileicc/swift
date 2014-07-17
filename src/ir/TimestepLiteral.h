#pragma once

#include "ConstSymbol.h"

namespace swift {
namespace ir {

class TimestepLiteral: public swift::ir::ConstSymbol {
public:
  TimestepLiteral(unsigned v = 0);
  virtual ~TimestepLiteral();

  unsigned getValue() const;
  void print(FILE* file, int indent) const ;
private:
  unsigned value;
};

}
}
