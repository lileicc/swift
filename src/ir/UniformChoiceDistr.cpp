#include "UniformChoiceDistr.h"
#include "SetExpr.h"

#include <string>

namespace swift {
namespace ir {

UniformChoiceDistr::UniformChoiceDistr(std::shared_ptr<SetExpr> b) :
    Distribution(std::string("UniformChoice")), body(b) {
}

UniformChoiceDistr::~UniformChoiceDistr() {
}

std::shared_ptr<SetExpr> UniformChoiceDistr::getBody() const {
  return body;
}

void UniformChoiceDistr::print(FILE* file, int indent) const {
  fprintf(file, "%*sUniformChoiceDistr:\n", indent, "");
  body->print(file, indent + 2);
}

}
}
