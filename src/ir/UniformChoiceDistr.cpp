#include "UniformChoiceDistr.h"

#include <string>

namespace swift { namespace ir {

UniformChoiceDistr::UniformChoiceDistr(std::shared_ptr<SetExpr> b)
  :Distribution(std::string("UniformChoice")), body(b) {
}

UniformChoiceDistr::~UniformChoiceDistr() {
}

std::shared_ptr<SetExpr> UniformChoiceDistr::getBody() const {
  return body;
}

}
}