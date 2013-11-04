#pragma once

#include <vector>

#include "Clause.h"
#include "OriginAttr.h"
#include "Ty.h"
//#include "TypeDomain.h"

namespace swift { namespace ir {
class TypeDomain;

class NumberStmt {
  TypeDomain* refer;
  std::vector<OriginAttr*> origin;
  std::vector<std::string> var;
public:
  NumberStmt(TypeDomain* refer);
  virtual ~NumberStmt();

  size_t size();
  OriginAttr* getOrigin(int k);
  const std::string& getVar(int k);
  TypeDomain* getRefer();

  void addArg(OriginAttr* o, std::string v);
};

}
}