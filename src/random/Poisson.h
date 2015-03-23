/*
 * Poisson.h
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Poisson: public swift::random::SwiftDistribution<int> {
public:
  Poisson();
  virtual ~Poisson();
  void init(double lambda);
  int gen();
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::poisson_distribution<int> dist;
  double lambda;
  double loglambda;
  bool is_dist_ok, is_coef_ok;
};

} /* namespace random */
} /* namespace swift */
