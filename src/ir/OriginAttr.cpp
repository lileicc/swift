#include "OriginAttr.h"

#include "Ty.h"
#include "TypeDomain.h"

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

void OriginAttr::print(FILE* file, int indent){
  fprintf(file, "%*s(OriginAttr:\n", indent, "");
  fprintf(file, "%*s:name %s\n", indent+2, "", getName().c_str());
  fprintf(file, "%*s:type %s\n", indent+2, "", getTyp()->toString().c_str());
  fprintf(file, "%*s:TypeDomain %s\n", indent+2, "", src->getName().c_str());
  fprintf(file, "%*s)\n", indent, "");
  
}

}
}
