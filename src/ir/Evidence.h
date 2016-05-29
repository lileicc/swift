#pragma once

#include <memory>
#include <vector>
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class Evidence {
public:
  Evidence(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);
  Evidence(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right, 
           std::vector<std::shared_ptr<VarDecl> > args, std::shared_ptr<Expr> cond = nullptr);
  virtual ~Evidence();

  const std::shared_ptr<Expr>& getLeft() const;
  const std::shared_ptr<Expr>& getRight() const;

  // for loop associated
  bool hasForLoop() const;
  const std::shared_ptr<Expr>& getCond() const;
  const std::shared_ptr<VarDecl> getArg(int k) const;
  const std::vector<std::shared_ptr<VarDecl> >& getArgs() const;
  const int argSize() const;
  // Temporal Features
  bool isTemporal() const;
  std::shared_ptr<VarDecl> getTemporalArg();
  void processTemporal(const Ty* timety);
  /*
   * not isTemporal() --> getTimestep() == 0
   *     isTemporal() --> / getTimestep() == -1: there is a temporal for-loop
   *                      \ getTimestep() == constant: fixed timestep evidence
   */
  void setTimestep(int t);
  int getTimestep() const;

  void print(FILE* file, int indent);

private:
  // Note: left can only be [ FunctionCall | #TypeName ]
  std::shared_ptr<Expr> left;
  // Note: right can only be non-random expression
  std::shared_ptr<Expr> right;

  // whether this obs stmt has a for-loop
  bool flag_forloop; 
  // var decls in the for loop
  std::vector<std::shared_ptr<VarDecl> > args;
  // temporal argument in the for loop
  bool istmp;
  std::shared_ptr<VarDecl> tmparg;
  int ts;
  // condition in the for loop
  std::shared_ptr<Expr> cond;
};

}
}
