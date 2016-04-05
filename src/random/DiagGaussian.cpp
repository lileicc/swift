/*
 * DiagGaussian.cpp
 *
 * Diagonal Multivariate Gaussian (normal) distribution with parameters
 * mean and covvector. The covvector should be the entries along the diagonal
 * of the covariance matrix.
 *
 *  Created on: March 11, 2016
 *      Author: Tony Duan
 */

#include <cmath>
#include <cassert>
#include "DiagGaussian.h"

namespace swift {
namespace random {

DiagGaussian::DiagGaussian()
    :dist(0.0,1.0),
    is_gen_ok(false), is_loglike_ok(false),
    sqrt2PI(std::sqrt(2*PI)), log2PI(std::log(2*PI)) {
}

DiagGaussian::~DiagGaussian() {
}

void DiagGaussian::init(const arma::mat& _mean, const arma::mat& _covvector) {
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

arma::mat DiagGaussian::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine); });
  return mean + arma::sqrt(covvector) % c;
}

double DiagGaussian::likeli(const arma::mat& x) {
  return std::exp(loglikeli(x)); // might not be the most efficient way?
}

double DiagGaussian::loglikeli(const arma::mat& x) {
  if(!is_loglike_ok) {
    log_coef = -0.5 * k * log2PI - 0.5 * arma::accu(covvector);
    is_loglike_ok = true;
  }
  arma::mat v = x - mean;
  return log_coef - 0.5 * arma::accu(arma::square(v) / covvector);
}

} /* namespace random */
} /* namespace swift */
