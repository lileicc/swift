#include "Query.h"
#include "VarDecl.h"

namespace swift {
namespace ir {

Query::Query(std::shared_ptr<Expr> var, std::string strExpr, bool general) :
    var(var),  strExpr(strExpr), general(general), flag_forloop(false), istmp(false), tmparg(nullptr), cond(nullptr) {
}
Query::Query(std::shared_ptr<Expr> var, std::vector<std::shared_ptr<VarDecl> > args,
  std::string strExpr, bool general, std::shared_ptr<Expr> cond) :
  var(var), strExpr(strExpr), general(general), args(args), istmp(false), tmparg(nullptr), cond(cond) {
  if (args.size() == 0) {
    flag_forloop = false;
    cond = nullptr; // Condition is only allowed when args is non-empty
  } else {
    flag_forloop = true;
  }
}

Query::~Query() {
}

bool Query::isGeneral() const {
  return general;
}

bool Query::isSpecial() const {
  return !general;
}

const std::shared_ptr<Expr>& Query::getVar() const {
  return var;
}

const std::string& Query::str() const {
  return strExpr;
}

bool Query::hasForLoop() const {
  return flag_forloop;
}

const std::shared_ptr<Expr>& Query::getCond() const {
  return cond;
}

const std::shared_ptr<VarDecl> Query::getArg(int k) const {
  return args[k];
}

const std::vector<std::shared_ptr<VarDecl> >& Query::getArgs() const {
  return args;
}

const int Query::argSize() const {
  return args.size();
}

bool Query::isTemporal() const {
  return istmp;
}

std::shared_ptr<VarDecl> Query::getTemporalArg() {
  return tmparg;
}

void Query::processTemporal(const Ty* timety) {
  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i]->getTyp() == timety) {
      istmp = true;
      tmparg = args[i];
      args.erase(args.begin() + i);
      break;
    }
  }
}

void Query::print(FILE* file, int indent) {
  fprintf(file, "%*sQuery:\n", indent, "");
  getVar()->print(file, indent + 2);

  if (flag_forloop) {
    fprintf(file, "%*sFor: ", indent + 2, "");
    if (istmp) {
      fprintf(file, "  %s", tmparg->toString().c_str());
    }
    for (int i = 0; i < args.size(); ++i) {
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
