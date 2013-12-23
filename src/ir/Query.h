#pragma once

#include "FunctionCall.h"

namespace swift { namespace ir {

class Query {
public:
  Query(std::shared_ptr<FunctionCall> var);
  virtual ~Query();

  const std::shared_ptr<FunctionCall>& getVar() const;

private:
  std::shared_ptr<FunctionCall> var;
};

}
}