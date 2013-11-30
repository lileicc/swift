#pragma once

#include <memory>
#include "FunctionCall.h"

namespace swift { namespace ir {

class Query {
public:
  Query(std::shared_ptr<FunctionCall> var);
  virtual ~Query();

  std::shared_ptr<FunctionCall> getVar();

private:
  std::shared_ptr<FunctionCall> var;
};

}
}