#pragma once

#include <vector>
#include <string>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class NumberStmt {
public:
  NumberStmt(TypeDomain* refer);
  virtual ~NumberStmt();

  size_t size();
  const OriginAttr* getOrigin(int k) const;
  const std::shared_ptr<VarDecl>& getVar(int k) const;
  const std::vector<std::shared_ptr<VarDecl>>& getAllVars() const;
  TypeDomain* getRefer() const;
  const std::shared_ptr<Clause>& getBody() const;

  void addArg(const OriginAttr* o, std::string v);
  void setExpr(std::shared_ptr<Clause> c);

private:
  TypeDomain* refer;
  std::vector<const OriginAttr*> origin;
  std::vector<std::shared_ptr<VarDecl> > var;
  std::shared_ptr<Clause> body;
};

}
}
