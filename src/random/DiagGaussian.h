/*
 * DiagGaussian.h
 *
 * Diagonal Multivariate Gaussian (normal) distribution with parameters
 * mean and covvector.
 *
 *  Created on: March 11, 2016
 *      Author: Tony Duan
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

#include "armadillo"

namespace swift {
namespace random {

class DiagGaussian: public swift::random::SwiftDistribution<arma::mat> {

public:

  DiagGaussian();
  virtual ~DiagGaussian();
  void init(const arma::mat& mean, const arma::mat& covvector);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);

private:

  std::normal_distribution<double> dist;
  arma::mat mean;
  arma::mat covvector;
  int k; // dimension of the vector
  arma::mat c; // a temporary col vec used to compute samples
  arma::mat cov_inv;
  double log_coef;
  bool is_gen_ok, is_loglike_ok;
  const double sqrt2PI, log2PI;

};

} /* namespace random */
} /* namespace swift */
