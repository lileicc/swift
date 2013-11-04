#include "CardExpr.h"

namespace swift { namespace ir {
CardExpr::CardExpr() {
}

CardExpr::~CardExpr() {
}

void CardExpr::setRefer(Ty* t) {
  refer = t;
}

Ty* CardExpr::getRefer() {
  return refer;
}

}
}