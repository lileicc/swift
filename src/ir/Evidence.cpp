#include "Evidence.h"

#include "Expr.h"
#include "ConstSymbol.h"
#include "Ty.h"
#include "VarDecl.h"

namespace swift {
namespace ir {

Evidence::Evidence(std::shared_ptr<Expr> left,
    std::shared_ptr<Expr> right) :
    left(left), right(right), flag_forloop(false), istmp(false), tmparg(nullptr), ts(0), cond(nullptr) {
}

Evidence::Evidence(
  std::shared_ptr<Expr> left, std::shared_ptr<Expr> right,
  std::vector<std::shared_ptr<VarDecl> > args,
  std::shared_ptr<Expr> cond) :
  left(left), right(right), args(args), istmp(false), tmparg(nullptr), ts(0), cond(cond) {
  if (args.size() == 0) {
    flag_forloop = false;
    cond = nullptr; // Condition is only allowed when args is non-empty
  }
  else {
    flag_forloop = true;
  }
}

Evidence::~Evidence() {
}

const std::shared_ptr<Expr>& Evidence::getLeft() const {
  return left;
}

const std::shared_ptr<Expr>& Evidence::getRight() const {
  return right;
}

bool Evidence::hasForLoop() const {
  return flag_forloop;
}

const std::shared_ptr<Expr>& Evidence::getCond() const {
  return cond;
}

const std::shared_ptr<VarDecl> Evidence::getArg(int k) const {
  return args[k];
}

const std::vector<std::shared_ptr<VarDecl> >& Evidence::getArgs() const {
  return args;
}

const int Evidence::argSize() const {
  return args.size();
}

bool Evidence::isTemporal() const {
  return istmp;
}

std::shared_ptr<VarDecl> Evidence::getTemporalArg() {
  return tmparg;
}

void Evidence::setTimestep(int t) {
  ts = t;
  istmp = (t >= 0);
}

int Evidence::getTimestep() const {
  return ts;
}

void Evidence::processTemporal(const Ty* timety) {
  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i]->getTyp() == timety) {
      istmp = true;
      ts = -1;
      tmparg = args[i];
      args.erase(args.begin() + i);
      break;
    }
  }
}

void Evidence::print(FILE* file, int indent) {
  fprintf(file, "%*sEvidence:\n", indent, "");
  if (getLeft() != nullptr) {
    fprintf(file, "%*sleft: type = %s\n", indent + 2, "", getLeft()->getTyp()->toString().c_str());
    getLeft()->print(file, indent + 4);
  }
  if (getRight() != nullptr) {
    fprintf(file, "%*sright: type = %s\n", indent + 2, "", getRight()->getTyp()->toString().c_str());
    getRight()->print(file, indent + 4);
  }
  if (flag_forloop) {
    fprintf(file, "%*sFor: ", indent + 2, "");
    if (istmp) {
      fprintf(file, "  %s", tmparg->toString().c_str());
    }
    for (size_t i = 0; i < args.size(); ++i) {
      fprintf(file, "  %s", args[i]->toString().c_str());
    }
    fprintf(file, "\n");
    if (cond != nullptr) {
      fprintf(file, "%*sCond:\n", indent + 2, "");
      getCond()->print(file, indent + 4);
    }
  }
}

}
}
