#include <cstdio>
#include "BlogModel.h"

#include "Evidence.h"
#include "FuncDefn.h"
#include "Query.h"
#include "TypeDomain.h"

namespace swift {
namespace ir {

BlogModel::~BlogModel() {
}

void BlogModel::addFunction(std::shared_ptr<FuncDefn> func) {
  if (func->isFixed())
    fixFunc.push_back(func);
  else
    /* TODO : To Add VoidFuncCall
     if (func->argSize() == 0)
     voidFunc.push_back(func);
     else
     */
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

const std::vector<std::shared_ptr<FuncDefn>>& BlogModel::getRandFuncs() {
  return randFunc;
}

const std::vector<std::shared_ptr<Query>>& BlogModel::getQueries() {
  return query;
}

const std::vector<std::shared_ptr<Evidence>>& BlogModel::getEvidences() {
  return evidence;
}

BlogModel::BlogModel(const std::string name) :
    name(name), markov_order(0) {
}

const std::vector<std::shared_ptr<TypeDomain>>& BlogModel::getTypes() {
  return types;
}

const std::string& BlogModel::getName() const {
  return name;
}

// Temporal Features
void BlogModel::setMarkovOrder(int k) {
  markov_order = k;
}

int BlogModel::getMarkovOrder() const {
  return markov_order;
}

bool BlogModel::isTemporal() {
  return markov_order > 0;
}

void BlogModel::print(FILE* file, int indent) const {
  for (size_t i = 0; i < types.size(); i++) {
    types[i]->print(file, indent);
  }
  for (size_t i = 0; i < fixFunc.size(); i++) {
    fixFunc[i]->print(file, indent);
  }
  for (size_t i = 0; i < randFunc.size(); i++) {
    randFunc[i]->print(file, indent);
  }
  for (size_t i = 0; i < evidence.size(); i++) {
    evidence[i]->print(file, indent);
  }
  for (size_t i = 0; i < query.size(); i++) {
    query[i]->print(file, indent);
  }
}

void BlogModel::print(const char* filename) const {
  FILE* irf = stdout;
  if (filename && filename[0] != '\0')
    irf = fopen(filename, "w");
  this->print(irf);
  if (irf != stdout)
    fclose(irf);
}

}
}

