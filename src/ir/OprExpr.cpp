#include "OprExpr.h"

#include "Ty.h"

namespace swift {
namespace ir {

OprExpr::OprExpr(IRConstant op) :
    op(op) {
}

OprExpr::~OprExpr() {
}

IRConstant OprExpr::getOp() const {
  return op;
}

void OprExpr::print(FILE* file, int indent) const {
  fprintf(file, "%*sOprExpr: %d  type = %s\n", indent, "", op, getTyp()->toString().c_str());
  for (size_t i = 0; i < args.size(); i ++) {
    fprintf(file, "%*sarg#%d:\n", indent + 2, "", (int)i);
    args[i]->print(file, indent + 4);
  }
}

}
}
