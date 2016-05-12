/*
 * PrecisionGaussian.cpp
 *
 *  Created on: Sept 15, 2014
 *      Author: yiwu
 */

#include <cmath>
#include <cassert>
#include "PrecisionGaussian.h"

namespace swift {
namespace random {

PrecisionGaussian::PrecisionGaussian()
  : dist(0.0,1.0),
    is_gen_ok(false), is_like_ok(false), is_loglike_ok(false),
    sqrt2PI(std::sqrt(2*PI)), log2PI(std::log(2*PI)) {
}

PrecisionGaussian::~PrecisionGaussian() {
}

void PrecisionGaussian::init(const arma::mat& _mean, const arma::mat& _inv_cov) {
  mean = _mean;
  inv_cov = _inv_cov;
  // Dimension Check
  if (mean.n_cols > 1)
    mean = arma::trans(mean);
  assert(mean.n_cols == 1);
  assert(mean.n_rows == inv_cov.n_rows && inv_cov.n_cols == inv_cov.n_rows);

  is_gen_ok = false;
  is_like_ok = true;
  is_loglike_ok = true;

  // Variables for computing cpd
  k = mean.n_rows;
  det_cov = 1 / arma::det(inv_cov);
  coef = std::pow(sqrt2PI, -k) / std::sqrt(det_cov);
  log_coef = -k * 0.5 * log2PI - 0.5 * std::log(det_cov);
}

arma::mat PrecisionGaussian::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    A = arma::flipud(arma::fliplr(arma::inv(arma::chol(inv_cov))));
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine); });
  return mean + A * c;
}

double PrecisionGaussian::likeli(const arma::mat& x) {
  arma::mat v(x - mean);
  double rat = arma::as_scalar(arma::trans(v) * inv_cov * v);
  return coef * std::exp(-0.5 * rat);
}

double PrecisionGaussian::loglikeli(const arma::mat& x) {
  arma::mat v(x - mean);
  double rat = arma::as_scalar(arma::trans(v) * inv_cov * v);
  return log_coef - 0.5 * rat;
}

} /* namespace random */
} /* namespace swift */
