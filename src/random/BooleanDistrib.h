/*
 * BooleanDistrib.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class BooleanDistrib: public swift::random::SwiftDistribution<bool> {
public:
  BooleanDistrib();
  virtual ~BooleanDistrib();
  void init(double p);
  bool gen();
  double likeli(const bool& x);
  double loglikeli(const bool& x);
private:
  std::uniform_real_distribution<double> dist;
  double p;
  double logp;
  double log1_p;
  bool is_loglike_ok;
};

} /* namespace random */
} /* namespace swift */
