/*
 * Bernoulli.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Bernoulli: public swift::random::SwiftDistribution<int> {
public:
  Bernoulli();
  virtual ~Bernoulli();
  void init(double p);
  int gen();
  double likeli(int x);
  double loglikeli(int x);
private:
  std::bernoulli_distribution dist;
  double p;
  double logp;
  double log1_p;
};

} /* namespace random */
} /* namespace swift */
