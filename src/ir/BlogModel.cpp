#include "BlogModel.h"

#include "Evidence.h"
#include "FuncDefn.h"
#include "Query.h"
#include "TypeDomain.h"

namespace swift { namespace ir {

BlogModel::~BlogModel() {
}

void BlogModel::addFunction(std::shared_ptr<FuncDefn> func) {
  if (func->isFixed()) fixFunc.push_back(func);
  else
  if (func->argSize() == 0)
    voidFunc.push_back(func);
  else
    randFunc.push_back(func);
}

void BlogModel::addQuery(std::shared_ptr<Query> q) {
  query.push_back(q);
}

void BlogModel::addEvidence(std::shared_ptr<Evidence> e) {
  evidence.push_back(e);
}

void BlogModel::addTypeDomain(std::shared_ptr<TypeDomain> t) {
  types.push_back(t);
}

const std::vector<std::shared_ptr<FuncDefn>>& BlogModel::getFixFuncs() {
  return fixFunc;
}

const std::vector<std::shared_ptr<FuncDefn>>& BlogModel::getVoidFuncs() {
  return voidFunc;
}

const std::vector<std::shared_ptr<FuncDefn>>& BlogModel::getRandFuncs() {
  return randFunc;
}

const std::vector<std::shared_ptr<Query>>& BlogModel::getQueries() {
  return query;
}

const std::vector<std::shared_ptr<Evidence>>& BlogModel::getEvidences() {
  return evidence;
}

BlogModel::BlogModel(const std::string name): name(name) {
}

const std::vector<std::shared_ptr<TypeDomain>>& BlogModel::getTypes() {
  return types;
}

const std::string& BlogModel::getName() const {
  return name;
}

void BlogModel::print(FILE* file, int indent){
  fprintf(file, "%*s(FixFuncs:\n", indent, "");
  auto fixFuncs = getFixFuncs();
  for(size_t i = 0; i < fixFuncs.size(); i++){
    fixFuncs[i]->print(file, indent+2);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
