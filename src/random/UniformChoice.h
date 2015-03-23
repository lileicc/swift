/*
 * UniformChoice.h
 *
 *  Created on: Feb 8, 2014
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

class UniformChoice: public swift::random::SwiftDistribution<int> {
public:
  UniformChoice();
  ~UniformChoice();
  void init(std::vector<int> values);
  int gen();
  template<typename _RD>
  int gen(_RD& rd);
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::uniform_int_distribution<int> dist;
  std::vector<int> values; // values that this distribution will generation
  double weight, log_weight;
  std::unordered_map<int,int> ind; // value appear at which index
  int time_stamp; // record the total time of initializations
  const size_t SizeLimit = 200000; // When ind.size() reach this number, we perform clear()
  bool is_dist_ok, is_ind_ok;
};

} /* namespace random */
} /* namespace swift */
