/*
 * CategoricalDistribution.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <initializer_list>
#include <random>
#include <vector>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class CategoricalDistribution: public swift::random::SwiftDistribution<int> {
public:
  CategoricalDistribution(std::initializer_list<double> il);
  ~CategoricalDistribution();
  int gen();
  double likeli(int);
  double loglikeli(int);
private:
  std::discrete_distribution<int> dist;
  std::vector<double> weight;
  int has_null;
};

} /* namespace random */
} /* namespace swift */
