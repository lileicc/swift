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
    a(0), b(0) {
}

UniformReal::~UniformReal() {
}

void UniformReal::init(double a, double b) {
  if (a > b) std::swap(a, b);
  this->a = a;
  this->b = b;
  dist = std::uniform_real_distribution<double>(a, b);
}

double UniformReal::gen() {
  return dist(engine);
}

double UniformReal::likeli(const double& x) {
  return ((x >= a) && (x <= b)) ? 1.0 / (b - a) : 0;
}

double UniformReal::loglikeli(const double& x) {
  return ((x >= a) && (x <= b)) ? -std::log(b - a) : - INFINITY;
}

} /* namespace random */
} /* namespace swift */
