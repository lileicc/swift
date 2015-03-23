/*
 * Geometric.h
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Geometric: public swift::random::SwiftDistribution<int> {
public:
  Geometric();
  virtual ~Geometric();
  void init(double p);
  int gen();
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::geometric_distribution<int> dist;
  double p, q;
  double logp, logq;
  bool is_loglike_ok, is_dist_ok;
};

} /* namespace random */
} /* namespace swift */
