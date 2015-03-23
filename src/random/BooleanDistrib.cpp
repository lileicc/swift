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
    dist(0.0, 1.0), p(0.5), 
    logp(std::log(0.5)), log1_p(std::log(0.5)), is_loglike_ok(true) {
}

BooleanDistrib::~BooleanDistrib() {
}

void BooleanDistrib::init(double p) {
  if(p < 0) p = 0;
  if(p > 1) p = 1;
  if (p != this->p) {
    this->p = p;
    is_loglike_ok = false;
  }
}

bool BooleanDistrib::gen() {
  return dist(engine) < p;
}

double BooleanDistrib::likeli(const bool& x) {
  return x ? p : 1 - p;
}

double BooleanDistrib::loglikeli(const bool& x) {
  if (!is_loglike_ok) {
    logp = std::log(p);
    log1_p = std::log(1 - p);
    is_loglike_ok = true;
  }
  return x ? logp : log1_p;
}

} /* namespace random */
} /* namespace swift */
