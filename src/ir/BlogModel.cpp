#include "BlogModel.h"

#include "Evidence.h"
#include "FuncDefn.h"
#include "Query.h"
#include "TypeDomain.h"

namespace swift { namespace ir {

BlogModel::BlogModel() {
}


BlogModel::~BlogModel() {
}

void BlogModel::addFunction(FuncDefn* func) {
  if (func->isFixed()) fixFunc.push_back(func);
  else
  if (func->argSize() == 0)
    voidFunc.push_back(func);
  else
    randFunc.push_back(func);
}

void BlogModel::addQuery(Query* q) {
  query.push_back(q);
}

void BlogModel::addEvidence(Evidence* e) {
  evidence.push_back(e);
}

void BlogModel::addTypeDomain(TypeDomain* t) {
  types.push_back(t);
}

const std::vector<FuncDefn*>& BlogModel::getFixFuncs() {
  return fixFunc;
}

const std::vector<FuncDefn*>& BlogModel::getVoidFuncs() {
  return voidFunc;
}

const std::vector<FuncDefn*>& BlogModel::getRandFuncs() {
  return randFunc;
}

const std::vector<Query*>& BlogModel::getQueries() {
  return query;
}

const std::vector<Evidence*>& BlogModel::getEvidences() {
  return evidence;
}

const std::vector<TypeDomain*>& BlogModel::getTypes() {
  return types;
}

}
}