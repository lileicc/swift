#pragma once

#include <memory>
#include "FunctionCall.h"

namespace swift { namespace ir {

class Query {
public:
  Query(std::shared_ptr<Expr> var);
  virtual ~Query();

  // TODO refactor name
  const std::shared_ptr<Expr>& getVar() const;
  // For Debugging Use
  void print(FILE* file, int indent);

private:
  // Note: var can be [ FunctionCall | #TypeName ]
  std::shared_ptr<Expr> var;
};

}
}
