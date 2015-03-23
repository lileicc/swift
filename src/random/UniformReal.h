/*
 * UniformReal.h
 *
 *  Created on: Mar 16, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class UniformReal: public swift::random::SwiftDistribution<double> {
public:
  UniformReal();
  virtual ~UniformReal();
  void init(double a, double b);
  double gen();
  double likeli(const double& x);
  double loglikeli(const double& x);
private:
  std::uniform_real_distribution<double> dist;
  double a;
  double b;
  double scale, logscale;
  bool is_logscale_ok;
};

} /* namespace random */
} /* namespace swift */
