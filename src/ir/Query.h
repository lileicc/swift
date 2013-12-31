#pragma once

#include <memory>
#include "FunctionCall.h"

namespace swift { namespace ir {

class Query {
public:
  Query(std::shared_ptr<Expr> var);
  virtual ~Query();

  const std::shared_ptr<Expr>& getVar() const;

private:
  // Note: var can be [ FunctionCall | #TypeName ]
  std::shared_ptr<Expr> var;
};

}
}
