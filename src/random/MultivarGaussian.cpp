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

MultivarGaussian::MultivarGaussian() {
}

MultivarGaussian::~MultivarGaussian() {
}

void MultivarGaussian::init(arma::mat _mean, arma::mat _cov) {
  mean = _mean;
  cov = _cov;
  // Dimension Check
  if (mean.n_rows == 1)
    mean = trans(mean);
  assert(mean.n_cols == 1);
  assert(mean.n_rows == cov.n_rows && cov.n_cols == cov.n_rows);
  c.set_size(mean.n_rows, mean.n_cols);
  A = trans(chol(cov));
  dist = std::normal_distribution<double>(0, 1);

  // Variables for computing cpd
  k = mean.n_rows;
  inv_cov = inv_sympd(cov); // Assume it is positive definite!
  det_cov = det(cov);
  coef = std::pow(std::sqrt(PI * 2.0), -k) / std::sqrt(det_cov);
  log_coef = -k * 0.5 * std::log(2.0 * PI) - 0.5 * std::log(det_cov);
}

arma::mat MultivarGaussian::gen() {
  c.imbue([&]() { return dist(engine); });
  return mean + A * c;
}

double MultivarGaussian::likeli(const arma::mat& x) {
  arma::mat v(x - mean);
  double rat = as_scalar(trans(v) * inv_cov * v);
  return coef * std::exp(-0.5 * rat);
}

double MultivarGaussian::loglikeli(const arma::mat& x) {
  arma::mat v(x - mean);
  double rat = as_scalar(trans(v) * inv_cov * v);
  return log_coef - 0.5 * rat;
}

} /* namespace random */
} /* namespace swift */
