#include "StringLiteral.h"

#include "IRConst.h"

namespace swift { namespace ir {
StringLiteral::StringLiteral(const std::string& v)
  :ConstSymbol(IRConstant::STRINGLITERAL), value(v) {
}

StringLiteral::~StringLiteral() {
}

const std::string& StringLiteral::getValue() const {
  return value;
}

}
}