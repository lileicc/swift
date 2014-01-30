#pragma once
#include <cstdio>
#include "ConstSymbol.h"
#include "InstSymbol.h"

namespace swift {
namespace ir {
class InstSymbolRef: public swift::ir::ConstSymbol {
public:
  InstSymbolRef(const InstSymbol* inst = NULL);
  virtual ~InstSymbolRef();

  const InstSymbol* getInst() const;

  void print(FILE*, int) const;

private:
  const InstSymbol* inst;
};

}
}
