/*
 * Bernoulli.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Bernoulli.h"

namespace swift {
namespace random {

Bernoulli::Bernoulli() :
    dist(0.0,1.0), p(0) {
}

Bernoulli::~Bernoulli() {
}

void Bernoulli::init(double p) {
  if(p < 0) p = 0;
  if(p > 1) p = 1;
  this->p = p;
  logp = std::log(p);
  log1_p = std::log(1-p);
}

int Bernoulli::gen() {
  return dist(engine) < p;
}

double Bernoulli::likeli(const int& x) {
  return x ? p : (1 - p);
}

double Bernoulli::loglikeli(const int& x) {
  return x ? logp : log1_p;
}

} /* namespace random */
} /* namespace swift */
