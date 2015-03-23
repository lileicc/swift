/*
 * MultivarGaussian.h
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

class MultivarGaussian: public swift::random::SwiftDistribution<arma::mat> {
public:
  MultivarGaussian();
  virtual ~MultivarGaussian();
  void init(const arma::mat& mean, const arma::mat& cov);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);
private:
  std::normal_distribution<double> dist;
  arma::mat mean, cov;
  arma::mat A; // transpose of Cholesky Decomposition: A * A' = cov
  arma::mat c; // a temporary colvec used to compute samples : sample = mean + A * c
  arma::mat inv_cov; // inverse of the covariance matrix to compute cpd
  int k; // dimension of the vector
  double det_cov, coef, log_coef;
  bool is_gen_ok, is_like_ok, is_loglike_ok;
  const double sqrt2PI, log2PI;
};

} /* namespace random */
} /* namespace swift */
