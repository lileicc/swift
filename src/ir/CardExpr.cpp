#include "CardExpr.h"
#include "SetExpr.h"
#include "SetTy.h"

namespace swift { namespace ir {
CardExpr::CardExpr() : refer(NULL) {
}

CardExpr::~CardExpr() {
}

const Ty* CardExpr::getRefer() const {
  return refer;
}

void CardExpr::setBody(std::shared_ptr<SetExpr> b) {
  body = b;
  refer = ((const SetTy*)b->getTyp())->getRefer();
}

const std::shared_ptr<SetExpr>& CardExpr::getBody() const {
  return body;
}

void CardExpr::print(FILE* file, int indent){
  fprintf(file, "%*s(CardExpr:\n", indent, "");
  fprintf(file, "%*srefer: %s\n", indent+2, "", refer->toString().c_str());
  fprintf(file, "%*sbody:\n", indent+2, "");
  getBody()->print(file, indent+4);
  fprintf(file, "%*s)\n", indent, "");
}

}
}