#pragma once

#include <vector>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class NumberStmt {
public:
  NumberStmt(TypeDomain* refer);
  virtual ~NumberStmt();

  size_t size();
  OriginAttr* getOrigin(int k);
  VarDecl* getVar(int k);
  TypeDomain* getRefer();

  void addArg(OriginAttr* o, std::string v);

private:
  TypeDomain* refer;
  std::vector<OriginAttr*> origin;
  std::vector<VarDecl*> var;
};

}
}