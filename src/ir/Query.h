#pragma once

#include <memory>
#include <vector>
#include "FunctionCall.h"

namespace swift {
namespace ir {

class Query {
public:
  Query(std::shared_ptr<Expr> var, std::string stringExpr = "", bool general = false);
  Query(std::shared_ptr<Expr> var, std::vector<std::shared_ptr<VarDecl> > args,
        std::string stringExpr = "", bool general = false,
        std::shared_ptr<Expr> cond = nullptr);
  virtual ~Query();

  // TODO refactor name
  const std::shared_ptr<Expr>& getVar() const;
  // For Debugging Use
  void print(FILE* file, int indent);

  // for loop quantifying
  bool hasForLoop() const;
  const std::shared_ptr<Expr>& getCond() const;
  const std::shared_ptr<VarDecl> getArg(int k) const;
  const std::vector<std::shared_ptr<VarDecl> >& getArgs() const;
  const int argSize() const;
  // Temporal features
  bool isTemporal() const;
  std::shared_ptr<VarDecl> getTemporalArg();
  void processTemporal(const Ty* timety);

  // whether var is special or general
  bool isGeneral() const;
  bool isSpecial() const;

  // For pretty printing
  const std::string& str() const;
private:
  // Note: var can be
  //   >> Special: [ FunctionCall | #TypeName ]
  //   >> General: Any Other Expr
  std::shared_ptr<Expr> var;
  std::string strExpr;
  bool general;

  // whether this obs stmt has a for-loop
  bool flag_forloop; 
  // var decls in the for loop
  std::vector<std::shared_ptr<VarDecl> > args;
  // temporal argument in the for loop
  bool istmp;
  std::shared_ptr<VarDecl> tmparg;
  // condition in the for loop
  std::shared_ptr<Expr> cond;
};

}
}
