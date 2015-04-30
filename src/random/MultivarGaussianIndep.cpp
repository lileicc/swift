/*
 * MultivarGaussianIndep.cpp
 *
 *  Created on: Sept 15, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include <cassert>
#include "MultivarGaussianIndep.h"

namespace swift {
namespace random {

MultivarGaussianIndep::MultivarGaussianIndep()
  : dist(0.0, 1.0), stddev(1.0), var(1.0),
  is_like_ok(true), is_loglike_ok(true), is_gen_ok(false),
  sqrt_2PI(std::sqrt(2.0 * PI)) {
  coef = 1.0 / (stddev * sqrt_2PI);
  log_coef = -std::log(stddev * sqrt_2PI);
  scale = -0.5;
}

MultivarGaussianIndep::~MultivarGaussianIndep() {
}

void MultivarGaussianIndep::init(const arma::mat& _mean, const double& _cov) {
  mean = _mean;
  var = _cov;
  stddev = std::sqrt(var);
  is_like_ok = is_loglike_ok = is_gen_ok = false;
  scale = -0.5 / (var);
}

arma::mat MultivarGaussianIndep::gen() {
  if(!is_gen_ok) {
    c.set_size(mean.n_rows, mean.n_cols);
    is_gen_ok = true;
  }
  c.imbue([&]() { return dist(engine) * stddev; });
  return mean + c;
}

double MultivarGaussianIndep::likeli(const arma::mat& x) {
  if(!is_like_ok) {
    dim = x.n_rows * x.n_cols;
    coef = std::pow(stddev * sqrt_2PI, -dim);
    is_like_ok = true;
  }
  v = (x - mean);
  double rat = dot(v,v) * scale;
  return coef * std::exp(rat);
}

double MultivarGaussianIndep::loglikeli(const arma::mat& x) {
  if(!is_loglike_ok) {
    dim = x.n_rows * x.n_cols;
    log_coef = - std::log(stddev * sqrt_2PI) * dim;
    is_loglike_ok = true;
  }
  v = (x - mean);
  double rat = dot(v,v) * scale;
  return log_coef + rat;
}

} /* namespace random */
} /* namespace swift */
