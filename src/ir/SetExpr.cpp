#include "SetExpr.h"

namespace swift { namespace ir {

SetExpr::SetExpr(IRConstant kind)
  :kind(kind) {
}

SetExpr::~SetExpr() {
}

IRConstant SetExpr::getKind() const {
  return kind;
}

void SetExpr::print(FILE* file, int indent){

}

}
}