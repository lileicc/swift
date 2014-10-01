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
    dist(0.0,1.0), a(0), b(1), scale(1), logscale(0) {
  is_logscale_ok = true;
}

UniformReal::~UniformReal() {
}

void UniformReal::init(double a, double b) {
  if (a > b) std::swap(a, b);
  this->a = a;
  this->b = b;
  if (b - a != scale) {
    scale = b - a;
    is_logscale_ok = false;
  }
}

double UniformReal::gen() {
  return dist(engine) * scale + a;
}

double UniformReal::likeli(const double& x) {
  return ((x >= a) && (x <= b)) ? 1.0 / scale : 0;
}

double UniformReal::loglikeli(const double& x) {
  if ((x >= a) && (x <= b)) {
    if (!is_logscale_ok) {
      logscale = -std::log(scale);
      is_logscale_ok = true;
    }
    return logscale;
  } else
    return -INFINITY;
}

} /* namespace random */
} /* namespace swift */
