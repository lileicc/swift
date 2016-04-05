/*
 * UniformInt.h
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class UniformInt: public swift::random::SwiftDistribution<int> {
public:
  UniformInt();
  virtual ~UniformInt();
  void init(int a, int b);
  int gen();
  double likeli(const int& x);
  double loglikeli(const int& x);
private:
  std::uniform_int_distribution<int> dist;
  int a;
  int b;
  int det, len;
  double loglen;
  bool is_loglike_ok, is_dist_ok;
};

} /* namespace random */
} /* namespace swift */
