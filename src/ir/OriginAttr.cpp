#include "OriginAttr.h"

#include "Ty.h"

namespace swift { namespace ir {

OriginAttr::OriginAttr(const std::string& name, const Ty* ty, std::shared_ptr<TypeDomain> src, size_t id)
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

std::shared_ptr<TypeDomain> OriginAttr::getSrc() const {
  return src;
}

void OriginAttr::setID(size_t k) {
  id = k;
}

size_t OriginAttr::getID() const {
  return id;
}

}
}
