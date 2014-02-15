#pragma once
#include <memory>
#include <vector>
#include <string>
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class NumberStmt {
public:
  /**
   * construct Number statement for TypeDomain
   */
  NumberStmt(std::shared_ptr<TypeDomain> refer);
  virtual ~NumberStmt();

  /**
   * get number of origin attributes
   */
  size_t size() const;

  /**
   * get k-th Origin attribute
   */
  const OriginAttr* getOrigin(size_t k) const;

  /**
   * get k-th variable for origin attribute
   */
  const std::shared_ptr<VarDecl>& getVar(size_t k) const;

  /**
   * get all variables for origin attributes
   */
  const std::vector<std::shared_ptr<VarDecl>>& getAllVars() const;

  /**
   * get the underlying typedomain
   */
  std::shared_ptr<TypeDomain> getRefer() const;

  /**
   * get the body clause of this number statement
   */
  const std::shared_ptr<Clause>& getBody() const;

  void addArg(const OriginAttr* o, std::string v);
  void setBody(std::shared_ptr<Clause> c);
  void print(FILE* file, int indent);

private:
  std::shared_ptr<TypeDomain> refer;
  std::vector<const OriginAttr*> origin;
  std::vector<std::shared_ptr<VarDecl> > var;
  std::shared_ptr<Clause> body;
};

}
}
