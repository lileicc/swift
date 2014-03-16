/*
 * Geometric.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */
#include <cmath>
#include "Geometric.h"

namespace swift {
namespace random {

Geometric::Geometric() {
  p = 1;
}

Geometric::~Geometric() {
}

void Geometric::init(double p) {
  if (p < 0) p = 0;
  if (p > 1) p = 1;
  this->p = p;
  q = 1-p;
  logp = std::log(p);
  logq = std::log(q);
  dist = std::geometric_distribution<int>(p);
}

int Geometric::gen() {
  return dist(engine);
}

double Geometric::likeli(const int& x) {
  return pow(q, x) * p;
}

double Geometric::loglikeli(const int& x) {
  if (x < 0)
    return - INFINITY;
  return x * logq + p;
}
} /* namespace random */
} /* namespace swift */
