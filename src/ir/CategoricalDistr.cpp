#include "CategoricalDistr.h"

#include <string>

namespace swift { namespace ir {

CategoricalDistr::CategoricalDistr()
  :Distribution(std::string("Categorical")) {
}

CategoricalDistr::~CategoricalDistr() {
}

size_t CategoricalDistr::size() {
  return weights.size();
}

void CategoricalDistr::addWeight(double w) {
  weights.push_back(w);
}

double CategoricalDistr::getWeight(int k) {
  return weights[k];
}

const std::vector<double>& CategoricalDistr::getWeights() {
  return weights;
}

void CategoricalDistr::addSymbol(ConstSymbol* c) {
  symbols.push_back(c);
}

ConstSymbol* CategoricalDistr::getSymbol(int k) {
  return symbols[k];
}

const std::vector<ConstSymbol*>& CategoricalDistr::getSymbols() {
  return symbols;
}

}
}