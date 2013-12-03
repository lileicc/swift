<<<<<<< HEAD
/*
 * Evidence.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "Evidence.h"

namespace swift {
namespace absyn {

Evidence::Evidence(int l, int c, Expr* left, Expr* right) :
    Stmt(l, c), left(left), right(right) {
}

Evidence::~Evidence() {
  if (left != NULL)
    delete left;
  if (right != NULL)
    delete right;
}

Expr* Evidence::getLeft() {
  return left;
}

Expr* Evidence::getRight() {
  return right;
}

// For Debugging Use
void Evidence::print(FILE* file, int indent) {
  fprintf(file, "%*s(Evidence:\n", indent, "");
  if (left != NULL) {
    fprintf(file, "%*s:left\n", indent + 2, "");
    left->print(file, indent + 4);
  }
  if (right != NULL) {
    fprintf(file, "%*s:right\n", indent + 2, "");
    right->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
=======
/*
 * Evidence.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "Evidence.h"

namespace swift {
namespace absyn {

Evidence::Evidence(int l, int c, Expr* left, Expr* right) :
    Stmt(l, c), left(left), right(right) {
}

Evidence::~Evidence() {
  if (left != NULL)
    delete left;
  if (right != NULL)
    delete right;
}

Expr* Evidence::getLeft() {
  return left;
}

Expr* Evidence::getRight() {
  return right;
}

// For Debugging Use
void Evidence::print(FILE* file, int indent) {
  fprintf(file, "%*s(Evidence:\n", indent, "");
  if (left != NULL) {
    fprintf(file, "%*s:left\n", indent + 2, "");
    left->print(file, indent + 4);
  }
  if (right != NULL) {
    fprintf(file, "%*s:right\n", indent + 2, "");
    right->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
>>>>>>> d79902b80479f1d013f2b7ae5b5af4e1fd36aa21
