/*
 * UniformInt.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: leili
 */
#include <cmath>
#include "UniformInt.h"

namespace swift {
namespace random {

UniformInt::UniformInt() :
    a(0), b(1), det(1), logdet(0), dist(0,1) {
  is_loglike_ok = true;
  is_dist_ok = true;
}

UniformInt::~UniformInt() {
}

void UniformInt::init(int a, int b) {
  this->a = a;
  this->b = b;
  if (b >= a && b - a != det) {
    this->det = b - a;
    is_dist_ok = false;
    is_loglike_ok = false;
  }
}

int UniformInt::gen() {
  if (b >= a) {
    if (!is_dist_ok) {
      dist = std::uniform_int_distribution<int>(0, det);
      is_dist_ok = true;
    }
    return dist(engine) + a;
  } else
    return b;
}

double UniformInt::likeli(const int& x) {
  return ((x >= a) && (x <= b)) ? 1.0 / det : 0;
}

double UniformInt::loglikeli(const int& x) {
  if (x >= a && x <= b) {
    if (!is_loglike_ok) {
      logdet = -std::log(det);
      is_loglike_ok = true;
    }
    return logdet;
  } else
    return -INFINITY;
}

} /* namespace random */
} /* namespace swift */
