/*
 * BooleanDistrib.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "BooleanDistrib.h"

namespace swift {
namespace random {

BooleanDistrib::BooleanDistrib() :
    p(0), logp(0), log1_p(0) {
}

BooleanDistrib::~BooleanDistrib() {
}

void BooleanDistrib::init(double p) {
  if(p < 0) p = 0;
  if(p > 1) p = 1;
  this->p = p;
  logp = std::log(p);
  log1_p = std::log(1-p);
  dist = std::bernoulli_distribution(p);
}

bool BooleanDistrib::gen() {
  return dist(engine);
}

double BooleanDistrib::likeli(bool x) {
  return x ? p : 1 - p;
}

double BooleanDistrib::loglikeli(bool x) {
  return x ? logp : log1_p;
}

} /* namespace random */
} /* namespace swift */
