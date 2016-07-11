/*
 * MultivarGaussianIndep.h
 *
 *  Created on: Sept 15, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

#include "armadillo"

namespace swift {
namespace random {

class MultivarGaussianIndep: public swift::random::SwiftDistribution<arma::mat> {
public:
  MultivarGaussianIndep();
  virtual ~MultivarGaussianIndep();
  void init(const arma::mat& mean, const double& cov);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);
private:
  std::normal_distribution<double> dist;
  arma::mat mean, c, v;
  int dim;
  double stddev, var;
  double coef, log_coef, scale;
  bool is_like_ok, is_loglike_ok, is_gen_ok;
  const double sqrt_2PI;
};

} /* namespace random */
} /* namespace swift */
