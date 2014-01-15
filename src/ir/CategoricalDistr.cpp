#include "CategoricalDistr.h"

#include <string>

namespace swift { namespace ir {

CategoricalDistr::CategoricalDistr(const predecl::PreDeclDistr* refer)
  :Distribution(std::string("Categorical"), refer) {
}

CategoricalDistr::~CategoricalDistr() {
}

size_t CategoricalDistr::size() const {
  return weights.size();
}

void CategoricalDistr::addWeight(double w) {
  weights.push_back(w);
}

double CategoricalDistr::getWeight(int k) const {
  return weights[k];
}

const std::vector<double>& CategoricalDistr::getWeights() const {
  return weights;
}

void CategoricalDistr::addSymbol(std::shared_ptr<ConstSymbol> c) {
  symbols.push_back(c);
}

std::shared_ptr<ConstSymbol> CategoricalDistr::getSymbol(int k) const {
  return symbols[k];
}

const std::vector<std::shared_ptr<ConstSymbol> >& CategoricalDistr::getSymbols() const {
  return symbols;
}

void CategoricalDistr::print(FILE* file, int indent){
  
}

}
}