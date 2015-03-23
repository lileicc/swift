#pragma once

#include <memory>
#include "FunctionCall.h"

namespace swift {
namespace ir {

class Query {
public:
  Query(std::shared_ptr<Expr> var, std::string stringExpr = "", bool general = false);
  virtual ~Query();

  // TODO refactor name
  const std::shared_ptr<Expr>& getVar() const;
  // For Debugging Use
  void print(FILE* file, int indent);

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
};

}
}
