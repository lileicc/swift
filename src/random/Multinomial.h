/*
 * Multinomial.h
 *
 *  Created on: Feb 28, 2014
 *      Author: yiwu
 */

#pragma once
#include <cstdarg>
#include <random>
#include <vector>
#include "SwiftDistribution.h"

#include "armadillo"

namespace swift {
namespace random {

class Multinomial: public swift::random::SwiftDistribution<std::vector<int> > {
public:
  Multinomial();
  virtual ~Multinomial();
  void init(const double* begin, const double* end);
  void init(const arma::mat& wei);
  void init(const std::vector<double>& wei);
  void init(int n, const arma::mat& wei);
  void init(int n, const std::vector<double>& wei);
  std::vector<int> gen();
  std::vector<int> gen_small(int n);
  std::vector<int> gen_large(int n);
  double likeli(const std::vector<int>& x);
  double loglikeli(const std::vector<int>& x);
private:
  std::uniform_real_distribution<double> dist;
  std::vector<double> weight; // cumulative weight of event, 
  std::vector<double> log_weight;
  double sum_wei;
  int n; // number of trials
  std::vector<bool> is_logwei_ok;
  std::vector<int> tmp_keys; // temporal storage
};

} /* namespace random */
} /* namespace swift */
