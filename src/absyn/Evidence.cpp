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
    Stmt(l, c), left(left), right(right), cond(NULL) {
}

Evidence::Evidence(int l, int c, Expr* left, Expr* right, std::vector<VarDecl> vars) :
    Stmt(l, c), left(left), right(right), vardecls(vars), cond(NULL) {
}

Evidence::Evidence(int l, int c, Expr* left, Expr* right, std::vector<VarDecl> vars, Expr* cd) :
    Stmt(l, c), left(left), right(right), vardecls(vars), cond(cd) {
}

Evidence::~Evidence() {
  if (left != NULL)
    delete left;
  if (right != NULL)
    delete right;
  if (cond != NULL)
    delete cond;
}

Expr* Evidence::getLeft() {
  return left;
}

Expr* Evidence::getRight() {
  return right;
}

void Evidence::setLeft(Expr* e) {
  left = e;
}

void Evidence::setRight(Expr* e) {
  right = e;
}

Expr* Evidence::getCond() {
  return cond;
}

void Evidence::setCond(Expr* e) {
  cond = e;
}

const VarDecl& Evidence::getVarDecl(size_t i) const {
  return vardecls[i];
}

const std::vector<VarDecl>& Evidence::getVarDecls() const {
  return vardecls;
}

void Evidence::clear() {
  left = NULL;
  right = NULL;
  cond = NULL;
  vardecls.clear();
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
  if (vardecls.size() > 0) {
    fprintf(file, "%*s:enumVars\n", indent+2, "");
    for(size_t i = 0; i < vardecls.size(); i++){
      vardecls[i].print(file, indent+4);
    }
  }
  if (cond != NULL) {
    fprintf(file, "%*s:cond\n", indent+2, "");
    cond->print(file, indent+4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
