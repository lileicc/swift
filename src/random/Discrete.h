/*
 * Discrete.h
 *
 *  Created on: Feb 17, 2014
 *      Author: yiwu
 */

#pragma once
#include <vector>
#include <random>
#include <map>
#include <unordered_map>
#include <vector>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Discrete: public swift::random::SwiftDistribution<int> {
public:
  Discrete();
  ~Discrete();
  void init(std::vector<double> wei);
  int gen();
  template<typename _RD>
  int gen(_RD& rd);
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::discrete_distribution<int> dist;
  std::vector<double> weights; // weights for categorical distribution
  std::vector<double> log_weights; // for efficiency
};

} /* namespace random */
} /* namespace swift */
