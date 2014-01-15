#include "ArrayExpr.h"

namespace swift { namespace ir {

ArrayExpr::ArrayExpr() {
}

ArrayExpr::~ArrayExpr() {
}

void ArrayExpr::print(FILE* file, int indent){
  fprintf(file, "%*s(ArrayExpr:\n", indent, "");
  for(size_t i = 0; i < argSize(); i++){
    fprintf(file, "%*s:arg %s\n", indent+2, "", i);
    get(i)->print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}