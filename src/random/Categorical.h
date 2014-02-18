/*
 * Categorical.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
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

class Categorical: public swift::random::SwiftDistribution<int> {
public:
  Categorical();
  ~Categorical();
  void init(const std::map<int, double>& ws);
  void init(std::vector<int> val, std::vector<double> wei);
  int gen();
  template<typename _RD>
  int gen(_RD& rd);
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::discrete_distribution<int> dist;
  std::vector<int> values; // values that this distribution will generation
  std::vector<double> weights; // weights for categorical distribution
  std::unordered_map<int, int> values_to_indic; // value appear at which index
  std::vector<double> log_weights; // for efficiency
};

} /* namespace random */
} /* namespace swift */
