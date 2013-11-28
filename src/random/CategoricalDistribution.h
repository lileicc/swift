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
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class CategoricalDistribution: public swift::random::SwiftDistribution<int> {
public:
  CategoricalDistribution();
  ~CategoricalDistribution();
  void init(std::map<int, double>& weights);
  int gen();
  double likeli(int x);
  double loglikeli(int x);

private:
  std::discrete_distribution<int> dist;
  std::vector<int> keys; // keys for the value
  std::vector<double> ws; // weights for categorical distribution
};

} /* namespace random */
} /* namespace swift */
