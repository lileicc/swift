#pragma once

#include <vector>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class BlogModel {
public:
  BlogModel();
  virtual ~BlogModel();

  void addFunction(FuncDefn* func);
  void addQuery(Query* q);
  void addEvidence(Evidence* e);
  void addTypeDomain(TypeDomain* t);

  const std::vector<FuncDefn*>& getFixFuncs();
  const std::vector<FuncDefn*>& getVoidFuncs();
  const std::vector<FuncDefn*>& getRandFuncs();
  const std::vector<Query*>& getQueries();
  const std::vector<Evidence*>& getEvidences();
  const std::vector<TypeDomain*>& getTypes();

private:
  std::vector<FuncDefn*> fixFunc;
  std::vector<FuncDefn*> voidFunc;
  std::vector<FuncDefn*> randFunc;
  std::vector<Query*> query;
  std::vector<Evidence*> evidence;
  std::vector<TypeDomain*> types;
};

}
}