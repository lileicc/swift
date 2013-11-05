#pragma once

#include <string>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class VarDecl {
public:
  VarDecl(Ty* typ, const std::string& var);
  virtual ~VarDecl();

  Ty* getTyp();
  const std::string& getVar();

  virtual std::string toString();

private:
  std::string var;
  Ty* typ;
};

}
}