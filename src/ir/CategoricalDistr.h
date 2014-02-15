#pragma once

#include <vector>
#include <memory>

#include "Distribution.h"
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class CategoricalDistr: public swift::ir::Distribution {
public:
  CategoricalDistr(const predecl::PreDeclDistr* refer);
  virtual ~CategoricalDistr();

  size_t size() const;
  void addWeight(double w);
  double getWeight(size_t k) const;
  const std::vector<double>& getWeights() const;
  void addSymbol(std::shared_ptr<ConstSymbol> c);
  std::shared_ptr<ConstSymbol> getSymbol(size_t k) const;
  const std::vector<std::shared_ptr<ConstSymbol>>& getSymbols() const;
  void print(FILE* file, int indent) const;

private:
  std::vector<double> weights;
  std::vector<std::shared_ptr<ConstSymbol> > symbols;
};

}
}
