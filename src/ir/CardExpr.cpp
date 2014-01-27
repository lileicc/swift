#include "CardExpr.h"
#include "SetExpr.h"
#include "SetTy.h"

namespace swift { namespace ir {
CardExpr::CardExpr() : referTyp(NULL) {
}

CardExpr::~CardExpr() {
}

const Ty* CardExpr::getType() const {
  return referTyp;
}

void CardExpr::setBody(std::shared_ptr<SetExpr> b) {
  body = b;
  referTyp = ((const SetTy*)b->getTyp())->getRefer();
}

const std::shared_ptr<SetExpr>& CardExpr::getBody() const {
  return body;
}

}
}