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
using namespace arma;

namespace swift {
namespace random {

class MultivarGaussian: public swift::random::SwiftDistribution<mat> {
public:
  MultivarGaussian();
  virtual ~MultivarGaussian();
  void init(mat mean, mat cov);
  mat gen();
  double likeli(const mat& x);
  double loglikeli(const mat& x);
private:
  std::normal_distribution<double> dist;
  mat mean, cov;
  mat A; // transpose of Cholesky Decomposition: A * A' = cov
  mat c; // a temporary colvec used to compute samples : sample = mean + A * c
  mat inv_cov; // inverse of the covariance matrix to compute cpd
  int k; // dimension of the vector
  double det_cov, coef, log_coef;
};

} /* namespace random */
} /* namespace swift */
