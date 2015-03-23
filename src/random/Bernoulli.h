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
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::uniform_real_distribution<double> dist;
  double p;
  double logp;
  double log1_p;
  bool is_loglike_ok;
};

} /* namespace random */
} /* namespace swift */
