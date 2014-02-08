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
}

Poisson::~Poisson() {
}

void Poisson::init(double lambda) {
  this->lambda = lambda;
  loglambda = std::log(lambda);
  dist = std::poisson_distribution<int>(lambda);
}

int Poisson::gen() {
  return dist(engine);
}

double Poisson::likeli(int x) {
  return std::exp(loglikeli(x));
}

double Poisson::loglikeli(int x) {
  if (x < 0)
    return - INFINITY;
  double p = - lambda + x * loglambda - std::lgamma(x + 1.0);
  return p;
}
} /* namespace random */
} /* namespace swift */
