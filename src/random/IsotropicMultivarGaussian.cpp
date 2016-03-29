/*
 * IsotropicMultivarGaussian.cpp
 *
 * Isotropic Multivariate Gaussian (normal) distribution with parameters
 * mean and covscale. The covariance matrix is identity
 * times covscale.
 *
 *  Created on: March 11, 2016
 *      Author: Tony Duan
 */

#include <cmath>
#include <cassert>
#include "IsotropicMultivarGaussian.h"

namespace swift {
namespace random {

IsotropicMultivarGaussian::IsotropicMultivarGaussian()
    :dist(0.0,1.0),
    is_gen_ok(false), is_like_ok(false), is_loglike_ok(false),
    sqrt2PI(std::sqrt(2*PI)), log2PI(std::log(2*PI)) {
}

IsotropicMultivarGaussian::~IsotropicMultivarGaussian() {
}

void IsotropicMultivarGaussian::init(const arma::mat& _mean, double _covscale) {
  mean = _mean;
  covscale = _covscale;

  // dimension check
  if (mean.n_cols > 1)
    mean = arma::trans(mean);
  assert(mean.n_cols == 1);

  is_gen_ok = false;
  is_like_ok = false;
  is_loglike_ok = false;

  // Variables for computing cpd
  k = mean.n_rows;
}

arma::mat IsotropicMultivarGaussian::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine); });
  return mean + covscale * c;
}

double IsotropicMultivarGaussian::likeli(const arma::mat& x) {
  if(!is_like_ok) {
    arma::mat cov = covscale * arma::eye(k, k);
    inv_cov = arma::inv_sympd(cov); // Assume it is positive definite!
    det_cov = arma::det(cov);
    coef = std::pow(sqrt2PI, -k) / std::sqrt(det_cov);
    is_like_ok = true;
  }
  arma::mat v(x - mean);
  double rat = arma::as_scalar(arma::trans(v) * inv_cov * v);
  return coef * std::exp(-0.5 * rat);
}

double IsotropicMultivarGaussian::loglikeli(const arma::mat& x) {
  if(!is_loglike_ok) {
    k = mean.n_rows;
    arma::mat cov = covscale * arma::eye(k, k);
    inv_cov = arma::inv_sympd(cov); // Assume it is positive definite!
    double sign;
    arma::log_det(det_cov, sign, cov);
    log_coef = -k * 0.5 * log2PI - 0.5 * det_cov;
    is_loglike_ok = true;
  }
  arma::mat v(x - mean);
  double rat = arma::as_scalar(arma::trans(v) * inv_cov * v);
  return log_coef - 0.5 * rat;
}

} /* namespace random */
} /* namespace swift */
