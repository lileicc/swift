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

}
}