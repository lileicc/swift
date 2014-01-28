/*
 * Poisson.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */

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
  dist = std::poisson_distribution<int>(lambda);
}

int Poisson::gen() {
  return dist(engine);
}

double Poisson::likeli(int x) {
  return std::exp(loglikeli(x));
}

double Poisson::loglikeli(int x) {
  //// TODO CHANGE THIS
  return (x >= 0) ? 1 : - INFINITY;
}
} /* namespace random */
} /* namespace swift */
