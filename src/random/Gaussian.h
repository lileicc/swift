/*
 * Gaussian.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Gaussian: public swift::random::SwiftDistribution<double> {
public:
  Gaussian();
  virtual ~Gaussian();
  void init(double mean = 0.0, double stddev = 1.0);
  double gen();
  double likeli(const double& x);
  double loglikeli(const double& x);
private:
  std::normal_distribution<double> dist;
  double mean, stddev, var;
  double coef, log_coef, scale;
  bool is_like_ok, is_loglike_ok;
  const double sqrt_2PI;
};

} /* namespace random */
} /* namespace swift */
