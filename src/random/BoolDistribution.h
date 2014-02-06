/*
 * BoolDistribution.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class BoolDistribution: public swift::random::SwiftDistribution<bool> {
public:
  BoolDistribution();
  virtual ~BoolDistribution();
  void init(double p);
  bool gen();
  double likeli(bool x);
  double loglikeli(bool x);
private:
  std::bernoulli_distribution dist;
  double p;
};

} /* namespace random */
} /* namespace swift */
