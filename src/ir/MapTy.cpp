#include "MapTy.h"

namespace swift {
namespace ir {

MapTy::MapTy(const Ty* from, const Ty* to)
  :Ty(IRConstant::MAP), from(from), to(to) {
}

MapTy::~MapTy() {
}

const Ty* MapTy::getFrom() const {
  return from;
}

const Ty* MapTy::getTo() const {
  return to;
}

std::string MapTy::toString() const {
  return std::string("map<") + (from == NULL ? "NULL" : from->toString()) + "," 
    + (to == NULL ? "NULL" : to->toString());
}

}
}