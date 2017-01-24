/*
 * Laplace.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: nishdesai
 */
#include <cmath>
#include "Laplace.h"

namespace swift {
namespace random {

Laplace::Laplace() {
  mu = 0.0;
  b = 1.0;
  log_b = 0.0;
  is_loglike_ok = true;
  dist = std::uniform_real_distribution<double>(-0.5,0.5);
}

Laplace::~Laplace() {
}

void Laplace::init(double mu, double b) {
  if (b <= 0) b = 1e-8;
  this->mu = mu;
  if (b != this->b) {
    this->b = b;
    is_loglike_ok = false;
  }
}

double Laplace::gen() {
  double u = dist(engine);
  int sg = (u <= 0 ? -1 : 1);
  return mu - b * sg * log(1 - 2 * abs(u));
}

double Laplace::likeli(const double& x) {
  return 0.5 / b * exp(-abs(x - mu) / b);
}

double Laplace::loglikeli(const double& x) {
  if (!is_loglike_ok) {
    log_b = std::log(2 * b);
    is_loglike_ok = true;
  }
  return -log_b + (-abs(x - mu) / b);
}
} /* namespace random */
} /* namespace swift */
