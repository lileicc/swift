#include "MapTy.h"

namespace swift {
namespace ir {

MapTy::MapTy(IRConstant typ, Ty* from, Ty* to)
  :Ty(typ), from(from), to(to) {
}

MapTy::~MapTy() {
}

Ty* MapTy::getFrom() {
  return from;
}

Ty* MapTy::getTo() {
  return to;
}

}
}