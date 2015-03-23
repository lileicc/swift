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
  p = q = 0.5;
  logp = logq = std::log(0.5);
  is_loglike_ok = true;
  dist = std::geometric_distribution<int>(0.5);
  is_dist_ok = true;
}

Geometric::~Geometric() {
}

void Geometric::init(double p) {
  if (p < 0) p = 0;
  if (p > 1) p = 1;
  if (p != this->p) {
    this->p = p;
    q = 1 - p;
    is_loglike_ok = false;
    is_dist_ok = false;
  }
}

int Geometric::gen() {
  if (!is_dist_ok) {
    dist = std::geometric_distribution<int>(p);
    is_dist_ok = true;
  }
  return dist(engine);
}

double Geometric::likeli(const int& x) {
  return pow(q, x) * p;
}

double Geometric::loglikeli(const int& x) {
  if (x < 0)
    return - INFINITY;
  if (!is_loglike_ok) {
    logp = std::log(p);
    logq = std::log(q);
    is_loglike_ok = true;
  }
  return x * logq + logp;
}
} /* namespace random */
} /* namespace swift */
