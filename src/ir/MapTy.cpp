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

std::string MapTy::toString() {
  return std::string("map<") + (from == NULL ? "NULL" : from->toString()) + "," 
    + (to == NULL ? "NULL" : to->toString());
}

}
}