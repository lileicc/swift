/*
 * MultivarGaussian.cpp
 *
 *  Created on: Sept 15, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include <cassert>
#include "MultivarGaussian.h"

namespace swift {
namespace random {

MultivarGaussian::MultivarGaussian()
  : dist(0.0,1.0),
    is_gen_ok(false), is_like_ok(false), is_loglike_ok(false),
    sqrt2PI(std::sqrt(2*PI)), log2PI(std::log(2*PI)) {
}

MultivarGaussian::~MultivarGaussian() {
}

void MultivarGaussian::init(const arma::mat& _mean, const arma::mat& _cov) {
  mean = _mean;
  cov = _cov;
  // Dimension Check
  if (mean.n_cols > 1)
    mean = arma::trans(mean);
  assert(mean.n_cols == 1);
  assert(mean.n_rows == cov.n_rows && cov.n_cols == cov.n_rows);
  
  is_gen_ok = false;
  is_like_ok = false;
  is_loglike_ok = false;
  
  

  // Variables for computing cpd
  k = mean.n_rows;
  inv_cov = arma::inv_sympd(cov); // Assume it is positive definite!
  det_cov = arma::det(cov);
  coef = std::pow(std::sqrt(PI * 2.0), -k) / std::sqrt(det_cov);
  log_coef = -k * 0.5 * std::log(2.0 * PI) - 0.5 * std::log(det_cov);
}

arma::mat MultivarGaussian::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    A = arma::trans(arma::chol(cov));
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine); });
  return mean + A * c;
}

double MultivarGaussian::likeli(const arma::mat& x) {
  if(!is_like_ok) {
    inv_cov = arma::inv_sympd(cov); // Assume it is positive definite!
    det_cov = arma::det(cov);
    coef = std::pow(sqrt2PI, -k) / std::sqrt(det_cov);
    is_like_ok = true;
  }
  arma::mat v(x - mean);
  double rat = arma::as_scalar(arma::trans(v) * inv_cov * v);
  return coef * std::exp(-0.5 * rat);
}

double MultivarGaussian::loglikeli(const arma::mat& x) {
  if(!is_loglike_ok) {
    k = mean.n_rows;
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
