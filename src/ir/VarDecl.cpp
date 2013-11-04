#include "VarDecl.h"

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

}
}