/*
 * CategoricalDistribution.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <vector>
#include <random>
#include <map>
#include <cmath>
#include <vector>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Categorical: public swift::random::SwiftDistribution<int> {
public:
  Categorical();
  ~Categorical();
  void init(std::map<int, double>& weights);
  template <typename _RD>
  int gen(_RD& rd);
  double likeli(int x);
  double loglikeli(int x);
private:
  std::discrete_distribution<int> dist;
  std::vector<int> keys; // keys for the value
  std::vector<double> weight; // weights for categorical distribution
};

} /* namespace random */
} /* namespace swift */
