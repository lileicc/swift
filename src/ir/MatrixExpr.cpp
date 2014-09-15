#include "MatrixExpr.h"

namespace swift {
namespace ir {

MatrixExpr::MatrixExpr(): flag_colvec(false), flag_rowvec(false) {
}

MatrixExpr::~MatrixExpr() {
}

void MatrixExpr::setRowVecFlag(bool flag) {
  flag_rowvec = flag;
}

bool MatrixExpr::isRowVec() {
  return flag_rowvec;
}

void MatrixExpr::setColVecFlag(bool flag) {
  flag_colvec = flag;
}

bool MatrixExpr::isColVec() {
  return flag_colvec;
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
