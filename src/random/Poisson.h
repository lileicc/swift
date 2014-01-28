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
  double likeli(int x);
  double loglikeli(int x);
private:
  std::poisson_distribution<int> dist;
  double lambda;
};

} /* namespace random */
} /* namespace swift */
