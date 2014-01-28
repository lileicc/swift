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
    a(0), b(0) {
}

UniformInt::~UniformInt() {
}

void UniformInt::init(int a, int b) {
  this->a = a;
  this->b = b;
  if (b >= a)
    dist = std::uniform_int_distribution<int>(a, b);
}

int UniformInt::gen() {
  return b >= a ? dist(engine) : b;
}

double UniformInt::likeli(int x) {
  return ((x >= a) && (x <= b)) ? 1.0 / (b - a) : 0;
}

double UniformInt::loglikeli(int x) {
  return ((x >= a) && (x <= b)) ? -std::log(b - a) : - INFINITY;
}

} /* namespace random */
} /* namespace swift */
