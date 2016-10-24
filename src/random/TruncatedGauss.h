/*
 * TruncatedGauss.h
 *
 *  Created on: Oct 24, 2016
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class TruncatedGauss: public swift::random::SwiftDistribution<double> {
public:
  TruncatedGauss();
  virtual ~TruncatedGauss();
  void init(double mean = 0.0, double stddev = 1.0, double l = -1, double r = 1);
  double gen();
  double likeli(const double& x);
  double loglikeli(const double& x);
private:
  double gen_trunc01(double l, double r);
  std::normal_distribution<double> dist;
  std::uniform_real_distribution<double> dist_unif;
  double mean, stddev, var;
  double lt, rt, l_cdf, r_cdf, mid_cdf, inv_mid_cdf;
  double shft_lt, shft_rt;
  double coef, log_coef, scale;
  bool is_like_ok, is_loglike_ok;
  const double sqrt_2PI;
};

} /* namespace random */
} /* namespace swift */
