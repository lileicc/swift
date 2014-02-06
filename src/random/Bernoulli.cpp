/*
 * Bernoulli.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Bernoulli.h"

namespace swift {
namespace random {

Bernoulli::Bernoulli() :
    p(0) {
}

Bernoulli::~Bernoulli() {
}

void Bernoulli::init(double p) {
  if(p < 0) p = 0;
  if(p > 1) p = 1;
  this->p = p;
  dist = std::bernoulli_distribution(p);
}

int Bernoulli::gen() {
  return dist(engine);
}

double Bernoulli::likeli(int x) {
  return x >= 1 ? p : 1 - p;
}

double Bernoulli::loglikeli(int x) {
  return -std::log(x >= 1 ? p : 1 - p);
}

} /* namespace random */
} /* namespace swift */
