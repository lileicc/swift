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
#include <functional>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class UniformChoice: public swift::random::SwiftDistribution<int> {
public:
  UniformChoice();
  ~UniformChoice();
  void init(std::vector<int> values); // init for listset
  void initcond(std::function<bool(int)> cf); // init for cond_func
  void initapp(std::function<int(int)> af); // init for apply_fun
  void init(int n); // for general set
  int gen();
  int gen_general();
  int gen_fast();
  int gen_cond();
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::uniform_int_distribution<int> dist;
  std::vector<int> values; // values that this distribution will generation
  double weight, log_weight;
  std::unordered_map<int,int> ind; // value appear at which index
  int time_stamp; // record the total time of initializations
  const size_t SizeLimit = 200000; // When ind.size() reach this number, we perform clear()
  bool is_dist_ok, is_ind_ok, is_value_ok;
  bool is_general;
  int n;
  std::function<bool(int)> cond_func;
  std::function<int(int)> apply_func;
};

} /* namespace random */
} /* namespace swift */
