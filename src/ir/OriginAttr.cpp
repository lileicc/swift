#include "OriginAttr.h"

#include "Ty.h"

namespace swift { namespace ir {

OriginAttr::OriginAttr(const std::string& name, const Ty* ty, TypeDomain* src, int id)
  :name(name), typ(ty), src(src), id(id) {
}

OriginAttr::~OriginAttr() {
}

const std::string& OriginAttr::getName() const {
  return name;
}

const Ty* OriginAttr::getTyp() const {
  return typ;
}

TypeDomain* OriginAttr::getSrc() const {
  return src;
}

void OriginAttr::setID(int k) {
  id = k;
}

int OriginAttr::getID() const {
  return id;
}

}
}
