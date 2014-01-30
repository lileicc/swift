#pragma once

#include <string>

#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class VarDecl {
public:
  VarDecl(const Ty* typ, const std::string& var);
  virtual ~VarDecl();

  const Ty* getTyp() const;
  const std::string& getVarName() const;

  virtual std::string toString() const;
  virtual std::string toSignature() const;

private:
  const Ty* typ;
  std::string var;
};

}
}
