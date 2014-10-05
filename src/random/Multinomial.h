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
using namespace arma;

namespace swift {
namespace random {

class Multinomial: public swift::random::SwiftDistribution<std::vector<int> > {
public:
  Multinomial();
  virtual ~Multinomial();
  void init(const double* wei, int n);
  void init(const double* begin, const double* end);
  void init(const arma::mat& wei);
  void init(const std::vector<double>& wei);
  void init(int n, ...);
  void init(const arma::mat& wei, int k);
  void init(const std::vector<double>& wei, int k);
  std::vector<int> gen();
  std::vector<int> gen(int n);
  double likeli(const std::vector<int>& x);
  double loglikeli(const std::vector<int>& x);
private:
  std::uniform_real_distribution<double> dist;
  std::vector<double> weight;
  std::vector<double> log_weight;
  double sum_wei;
  int k;
  std::vector<bool> is_logwei_ok;
};

} /* namespace random */
} /* namespace swift */
