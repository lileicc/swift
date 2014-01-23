#pragma once

#include <string>

#include "ConstSymbol.h"

namespace swift { namespace ir {

class StringLiteral :
  public swift::ir::ConstSymbol {
public:
  StringLiteral(const std::string& v = std::string(""));
  virtual ~StringLiteral();

  const std::string& getValue() const;
  void print(FILE* file, int indent);

private:
  std::string value;
};

}
}