/*
 * Poisson.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */
#include <cmath>
#include "Poisson.h"

namespace swift {
namespace random {

Poisson::Poisson() {
  lambda = 1;
  loglambda = 0;
  is_coef_ok = true;
  dist = std::poisson_distribution<int>(1);
  is_dist_ok = true;
}

Poisson::~Poisson() {
}

void Poisson::init(double lambda) {
  if (lambda != this->lambda) {
    this->lambda = lambda;
    is_coef_ok = false;
    is_dist_ok = false;
  }
}

int Poisson::gen() {
  if (!is_dist_ok) {
    dist = std::poisson_distribution<int>(lambda);
    is_dist_ok = true;
  }
  return dist(engine);
}

double Poisson::likeli(const int& x) {
  return std::exp(loglikeli(x));
}

double Poisson::loglikeli(const int& x) {
  if (x < 0)
    return - INFINITY;
  if (!is_coef_ok) {
    loglambda = std::log(lambda);
    is_coef_ok = true;
  }
  double p = - lambda + x * loglambda - std::lgamma(x + 1.0);
  return p;
}
} /* namespace random */
} /* namespace swift */
