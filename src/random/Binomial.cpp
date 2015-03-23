/*
 * Binomial.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Binomial.h"

namespace swift {
namespace random {

Binomial::Binomial() :
    is_dist_ok(false), is_loglike_ok(false) {
}

Binomial::~Binomial() {
}

void Binomial::init(int n, double p) {
  this->n = n;
  this->p = p;
  is_dist_ok = false;
  is_loglike_ok = false;
}

int Binomial::gen() {
  if(!is_dist_ok) {
    dist = std::binomial_distribution<int>(n, p);
    is_dist_ok = true;
  }
  return dist(engine);
}

double Binomial::likeli(const int& x) {
  if (x<0||x>n)return 0;
  return std::exp(loglikeli(x));
}

double Binomial::loglikeli(const int& x) {
  if (x<0||x>n)return -INFINITY;
  if (!is_loglike_ok) {
    logp = std::log(p); logq = std::log(1 - p);
    logfactn = std::lgammal(n + 1);
    is_loglike_ok = true;
  }
  return logfactn - std::lgamma(x + 1) - std::lgamma(n - x + 1)
    + x * logp + (n - x) * logq;
}

} /* namespace random */
} /* namespace swift */
