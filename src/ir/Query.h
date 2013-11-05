#pragma once

#include "VoidFuncCall.h"

namespace swift { namespace ir {

class Query {
public:
  Query(VoidFuncCall* var);
  virtual ~Query();

  VoidFuncCall* getVar();

private:
  VoidFuncCall* var;
};

}
}