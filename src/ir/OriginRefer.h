#pragma once
#include "Expr.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class OriginRefer : public swift::ir::Expr {
 public:
  OriginRefer(const OriginAttr* refer, std::shared_ptr<Expr> var);
  virtual ~OriginRefer();

  /**
   *  get the origin field definition of this origin function
   *
   *  @return a point to origin field definition
   */
  const OriginAttr* getRefer() const;  // why not shared ptr??

  /**
   *  get the argument expression to which this origin function applies
   *
   *  @return a shared pointer to Expr
   */
  std::shared_ptr<Expr> getOriginArg() const;

  virtual std::string toString();
  void print(FILE* file, int indent) const;

 private:
  const OriginAttr* refer;
};

}
}
