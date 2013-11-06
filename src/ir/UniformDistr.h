#pragma once
#include "Distribution.h"

namespace swift { namespace ir {

class UniformDistr :
  public swift::ir::Distribution {
public:
  UniformDistr();
  virtual ~UniformDistr();
};

}
}