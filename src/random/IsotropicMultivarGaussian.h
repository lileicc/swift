/*
 * IsotropicMultivarGaussian.h
 *
 * Isotropic Multivariate Gaussian (normal) distribution with parameters
 * mean and covarianceScale. The covariance matrix is identity
 * times covarianceScale.
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

class IsotropicMultivarGaussian: public swift::random::SwiftDistribution<arma::mat> {

public:

  IsotropicMultivarGaussian();
  virtual ~IsotropicMultivarGaussian();
  void init(const arma::mat& mean, double covscale);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);

private:

  std::normal_distribution<double> dist;
  arma::mat mean;
  double covscale;
  arma::mat c; // a temporary col vec used to compute samples
  arma::mat inv_cov; // inverse of the covariance matrix to compute cpd
  int k; // dimension of the vector
  double det_cov, coef, log_coef;
  bool is_gen_ok, is_like_ok, is_loglike_ok;
  const double sqrt2PI, log2PI;

};

} /* namespace random */
} /* namespace swift */
