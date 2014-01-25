#pragma once
#include <memory>
#include <vector>
#include <string>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class NumberStmt {
public:
  NumberStmt(std::shared_ptr<TypeDomain> refer);
  virtual ~NumberStmt();

  size_t size() const;
  const OriginAttr* getOrigin(int k) const;
  const std::shared_ptr<VarDecl>& getVar(int k) const;
  const std::vector<std::shared_ptr<VarDecl>>& getAllVars() const;
  std::shared_ptr<TypeDomain> getRefer() const;
  const std::shared_ptr<Clause>& getBody() const;

  void addArg(const OriginAttr* o, std::string v);
  void setBody(std::shared_ptr<Clause> c);

private:
  std::shared_ptr<TypeDomain> refer;
  std::vector<const OriginAttr*> origin;
  std::vector<std::shared_ptr<VarDecl> > var;
  std::shared_ptr<Clause> body;
};

}
}
