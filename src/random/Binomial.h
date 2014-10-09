/*
 * Binomial.h
 *
 *  Created on: Oct 8, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Binomial: public swift::random::SwiftDistribution<int> {
public:
  Binomial();
  virtual ~Binomial();
  void init(int n, double p);
  int gen();
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::binomial_distribution<int> dist;
  int n;
  double p, logp, logq;
  long double logfactn;
  bool is_dist_ok, is_loglike_ok;
};

} /* namespace random */
} /* namespace swift */
