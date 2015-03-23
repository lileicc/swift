/*
 * Gaussian.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Gaussian.h"

namespace swift {
namespace random {

Gaussian::Gaussian() :
  dist(0.0, 1.0), mean(0.0), stddev(1.0), var(1.0),
  is_like_ok(true), is_loglike_ok(true),
  sqrt_2PI(std::sqrt(2.0 * PI)) {
  coef = 1.0 / (stddev * sqrt_2PI);
  log_coef = -std::log(stddev * sqrt_2PI);
  scale = -0.5;
}

Gaussian::~Gaussian() {
}

void Gaussian::init(double mean, double var) {
  this->mean = mean;
  if (var != this->var) {
    this->var = var;
    this->stddev = std::sqrt(var);
    is_like_ok = is_loglike_ok = false;
    scale = -0.5 / (var);
  }
}

double Gaussian::gen() {
  return dist(engine) * stddev + mean;
}

double Gaussian::likeli(const double& x) {
  if(!is_like_ok) {
    coef = 1.0 / (stddev * sqrt_2PI);
    is_like_ok = true;
  }
  return coef * std::exp(scale * (x - mean) * (x - mean));
}

double Gaussian::loglikeli(const double& x) {
  if(!is_loglike_ok) {
    log_coef = - std::log(stddev * sqrt_2PI);
    is_loglike_ok = true;
  }
  return scale * (x - mean) * (x - mean) + log_coef;
}

} /* namespace random */
} /* namespace swift */
