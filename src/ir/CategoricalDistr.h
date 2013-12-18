#pragma once

#include <vector>

#include "Distribution.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class CategoricalDistr :
  public swift::ir::Distribution {
public:
  CategoricalDistr();
  virtual ~CategoricalDistr();

  size_t size();
  void addWeight(double w);
  double getWeight(int k);
  const std::vector<double>& getWeights();
  void addSymbol(ConstSymbol* c);
  ConstSymbol* getSymbol(int k);
  const std::vector<ConstSymbol*>& getSymbols();

private:
  std::vector<double> weights;
  std::vector<ConstSymbol*> symbols; 
};

}
}