/*
 * UniformReal.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: yiwu
 */
#include <cmath>
#include <algorithm>
#include "UniformReal.h"

namespace swift {
namespace random {

UniformReal::UniformReal() :
    dist(0.0,1.0), a(0), b(0) {
}

UniformReal::~UniformReal() {
}

void UniformReal::init(double a, double b) {
  if (a > b) std::swap(a, b);
  this->a = a;
  this->b = b;
  scale = b - a;
}

double UniformReal::gen() {
  return dist(engine) * scale + a;
}

double UniformReal::likeli(const double& x) {
  return ((x >= a) && (x <= b)) ? 1.0 / scale : 0;
}

double UniformReal::loglikeli(const double& x) {
  return ((x >= a) && (x <= b)) ? -std::log(scale) : - INFINITY;
}

} /* namespace random */
} /* namespace swift */
