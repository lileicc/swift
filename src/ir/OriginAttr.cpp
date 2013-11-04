#include "OriginAttr.h"

#include "Ty.h"

namespace swift { namespace ir {

OriginAttr::OriginAttr(const std::string& name, Ty* ty, TypeDomain* src)
  :name(name), typ(ty), src(src), id(id) {
}

OriginAttr::~OriginAttr() {
}

const std::string& OriginAttr::getName() {
  return name;
}

Ty* OriginAttr::getTyp() {
  return typ;
}

TypeDomain* OriginAttr::getSrc()  {
  return src;
}

void OriginAttr::setID(int k) {
  id = k;
}

int OriginAttr::getID() {
  return id;
}

}
}