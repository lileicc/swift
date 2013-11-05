#include "VarDecl.h"

#include "Ty.h"

namespace swift { namespace ir {

VarDecl::VarDecl(Ty* typ, const std::string& var)
  :typ(typ), var(var) {
}

VarDecl::~VarDecl() {
}

Ty* VarDecl::getTyp()  {
  return typ;
}

const std::string& VarDecl::getVar()  {
  return var;
}

std::string VarDecl::toString() {
  return (typ == NULL ? std::string("NULL") : typ->toString()) + " " + var;
}

}
}