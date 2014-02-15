#include "OriginRefer.h"

namespace swift {
namespace ir {

OriginRefer::OriginRefer(const OriginAttr* refer, std::shared_ptr<Expr> var) :
    refer(refer){
      addArg(var);
}

OriginRefer::~OriginRefer() {
}

const OriginAttr* OriginRefer::getRefer() const {
  return refer;
}

std::shared_ptr<Expr> OriginRefer::getOriginArg() const {
  return get(0);
}

}
}
