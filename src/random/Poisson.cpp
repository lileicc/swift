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

void Poisson::init(double lambda){
  this->lambda = lambda;
}

int Poisson::gen() {
  return dist(engine);
}

} /* namespace random */
} /* namespace swift */
