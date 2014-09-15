#include "MatrixExpr.h"

namespace swift {
namespace ir {

MatrixExpr::MatrixExpr() {
}

MatrixExpr::~MatrixExpr() {
}

void MatrixExpr::print(FILE* file, int indent) const {
  fprintf(file, "%*sMatrixExpr:", indent, "");
  if (flag_rowvec && flag_colvec)
    fprintf(file, "  flag = scalar");
  else
  if (flag_rowvec)
    fprintf(file, "  flag = RowVec");
  else
  if (flag_colvec)
    fprintf(file, "  flag = ColVec");
  fprintf(file, "\n");
  for (size_t i = 0; i < argSize(); i++) {
    fprintf(file, "%*sarg%lu: \n", indent + 2, "", i);
    get(i)->print(file, indent + 4);
  }
}

}
}
