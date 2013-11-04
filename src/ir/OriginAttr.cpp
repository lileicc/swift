#include "OriginAttr.h"

namespace swift { namespace ir {

OriginAttr::OriginAttr(std::string name, Ty* ty, TypeDomain* src, int id)
  :name(name), typ(ty), src(src), id(id) {
}

OriginAttr::~OriginAttr() {
}

std::string& OriginAttr::getName() {
  return name;
}

Ty* OriginAttr::getTyp() {
  return typ;
}

}
}