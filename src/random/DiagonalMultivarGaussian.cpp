/*
 * DiagonalMultivarGaussian.cpp
 *
 * Diagonal Multivariate Gaussian (normal) distribution with parameters
 * mean and covvector.
 *
 *  Created on: March 11, 2016
 *      Author: Tony Duan
 */

#include <cmath>
#include <cassert>
#include "DiagonalMultivarGaussian.h"

namespace swift {
namespace random {

DiagonalMultivarGaussian::DiagonalMultivarGaussian()
    :dist(0.0,1.0),
    is_gen_ok(false), is_loglike_ok(false),
    sqrt2PI(std::sqrt(2*PI)), log2PI(std::log(2*PI)) {
}

DiagonalMultivarGaussian::~DiagonalMultivarGaussian() {
}

void DiagonalMultivarGaussian::init(const arma::mat& _mean, const arma::mat& _covvector) {
  mean = _mean;
  covvector = _covvector;

  // dimension check
  if (mean.n_cols > 1)
    mean = arma::trans(mean);
  if (covvector.n_cols > 1)
    covvector = arma::trans(covvector);
  assert(mean.n_cols == 1);
  assert(covvector.n_cols == 1);

  is_gen_ok = false;
  is_loglike_ok = false;

  // Variables for computing cpd
  k = mean.n_rows;
}

arma::mat DiagonalMultivarGaussian::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine); });
  return mean + covvector % c;
}

double DiagonalMultivarGaussian::likeli(const arma::mat& x) {
  return std::exp(loglikeli(x)); // might not be the most efficient way?
}

double DiagonalMultivarGaussian::loglikeli(const arma::mat& x) {
  if(!is_loglike_ok) {
    log_coef = -0.5 * log2PI - arma::accu(arma::log(covvector));
    cov_inv = arma::ones(k, 1) / arma::square(covvector);
    is_loglike_ok = true;
  }
  arma::mat v = x - mean;
  return log_coef - 0.5 * arma::accu(arma::square(v) % cov_inv);
}

} /* namespace random */
} /* namespace swift */
