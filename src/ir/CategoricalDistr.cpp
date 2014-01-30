#include "CategoricalDistr.h"
#include "ConstSymbol.h"

#include <string>

namespace swift {
namespace ir {

CategoricalDistr::CategoricalDistr(const predecl::PreDeclDistr* refer) :
    Distribution(std::string("Categorical"), refer) {
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

void CategoricalDistr::print(FILE* file, int indent) const {
  fprintf(file, "%*s(CategoricalDistr:\n", indent, "");
  for (size_t i = 0; i < size(); i++) {
    fprintf(file, "%*ssymbol %lu:\n", indent + 2, "", i);
    getSymbol(i)->print(file, indent + 4);
    fprintf(file, "%*sweight %lu: %f\n", indent + 2, "", i, getWeight(i));
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}
