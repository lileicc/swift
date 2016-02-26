/*
 * Exponential.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: nishdesai
 */
#include <cmath>
#include "Exponential.h"

namespace swift {
namespace random {

Exponential::Exponential() {
  lambda = 1.0;
  log_lambda = 0.0;
  is_loglike_ok = true;
  dist = std::exponential_distrbution<double>(lambda);
}

Exponential::~Exponential() {
}

void Exponential::init(double lambda) {
  if (lambda < 0) lambda = 0;
  if (lambda != this->lambda) {
    this->lambda = lambda;
    is_loglike_ok = false;
  }
  dist = std::exponential_distrbution<double>(lambda);
}

double Exponential::gen() {
  return dist(engine);
}

double Exponential::likeli(const double& x) {
  if (x < 0)
    return 0;
  return lambda * exp(-lambda * x);
}

double Exponential::loglikeli(const double& x) {
  if (x < 0)
    return -INFINITY;
  if (!is_loglike_ok) {
    log_lambda = std::log(lambda);
    is_loglike_ok = true;
  }
  return log_lambda + (-lambda * x);
}
} /* namespace random */
} /* namespace swift */
