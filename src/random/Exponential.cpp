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
  is_dist_ok = true;
}

Exponential::~Exponential() {
}

void Exponential::init(double lambda) {
  this->lambda = lambda;
  log_lambda = log(lambda);
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
  return log_lambda + (-lambda * x);
}
} /* namespace random */
} /* namespace swift */
