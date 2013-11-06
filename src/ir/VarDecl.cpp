#include "VarDecl.h"

#include "Ty.h"

namespace swift { namespace ir {

VarDecl::VarDecl(const Ty* typ, const std::string& var)
  :typ(typ), var(var) {
}

VarDecl::~VarDecl() {
}

const Ty* VarDecl::getTyp() const  {
  return typ;
}

const std::string& VarDecl::getVar() const {
  return var;
}

std::string VarDecl::toString() const {
  return (typ == NULL ? std::string("NULL") : typ->toString()) + " " + var;
}

}
}
