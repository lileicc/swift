#pragma once

#include <vector>
#include <string>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class BlogModel {
public:
  BlogModel(const std::string name = std::string("BLOGProgram"));
  virtual ~BlogModel();

  void addFunction(std::shared_ptr<FuncDefn> func);
  void addQuery(std::shared_ptr<Query> q);
  void addEvidence(std::shared_ptr<Evidence> e);
  void addTypeDomain(std::shared_ptr<TypeDomain> t);
  // For Debugging Use
  void print(FILE* file, int indent=0);

  const std::vector<std::shared_ptr<FuncDefn>>& getFixFuncs();
  const std::vector<std::shared_ptr<FuncDefn>>& getVoidFuncs();
  const std::vector<std::shared_ptr<FuncDefn>>& getRandFuncs();
  const std::vector<std::shared_ptr<Query>>& getQueries();
  const std::vector<std::shared_ptr<Evidence>>& getEvidences();
  const std::vector<std::shared_ptr<TypeDomain>>& getTypes();
  const std::string & getName() const;

private:
  std::vector<std::shared_ptr<FuncDefn>> fixFunc;
  std::vector<std::shared_ptr<FuncDefn>> voidFunc;
  std::vector<std::shared_ptr<FuncDefn>> randFunc;
  std::vector<std::shared_ptr<Query>> query;
  std::vector<std::shared_ptr<Evidence>> evidence;
  std::vector<std::shared_ptr<TypeDomain>> types;
  std::string name;
};

}
}
