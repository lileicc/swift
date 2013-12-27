#pragma once

#include <vector>
#include <memory>

#include "Distribution.h"
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class CategoricalDistr :
  public swift::ir::Distribution {
public:
  CategoricalDistr(const predecl::PreDeclDistr* refer);
  virtual ~CategoricalDistr();

  size_t size();
  void addWeight(double w);
  double getWeight(int k);
  const std::vector<double>& getWeights();
  void addSymbol(std::shared_ptr<ConstSymbol> c);
  std::shared_ptr<ConstSymbol> getSymbol(int k);
  const std::vector<std::shared_ptr<ConstSymbol>>& getSymbols();

private:
  std::vector<double> weights;
  std::vector<std::shared_ptr<ConstSymbol> > symbols; 
};

}
}