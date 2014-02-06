/*
 * BoolDistribution.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "BoolDistribution.h"

namespace swift {
namespace random {

BoolDistribution::BoolDistribution() :
    p(0) {
}

BoolDistribution::~BoolDistribution() {
}

void BoolDistribution::init(double p) {
  if(p < 0) p = 0;
  if(p > 1) p = 1;
  this->p = p;
  dist = std::bernoulli_distribution(p);
}

bool BoolDistribution::gen() {
  return dist(engine);
}

double BoolDistribution::likeli(bool x) {
  return x ? p : 1 - p;
}

double BoolDistribution::loglikeli(bool x) {
  return -std::log(x ? p : 1 - p);
}

} /* namespace random */
} /* namespace swift */
