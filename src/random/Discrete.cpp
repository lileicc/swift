/*
 * Discrete.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: yiwu
 */
#include <numeric>
#include <cmath>
#include "Discrete.h"

namespace swift {
namespace random {

Discrete::Discrete() {
}

Discrete::~Discrete() {
}

void Discrete::init(std::vector<double> wei) {
  weights = wei;
  log_weights.clear();
  for (auto w : weights) {
    log_weights.push_back(std::log(w));
  }
  /*
   Note: In VS2013, we have to rewrite the last line with the following code

   double* A = new double[weights.size()];
   for (int i = 0; i<weights.size(); ++i)A[i] = weights[i];
   auto lis = std::initializer_list<double>(A, A + weights.size());
   dist = std::discrete_distribution<int>(lis);
   delete[weights.size()] A;
   */
  dist = std::discrete_distribution<int>(weights.begin(), weights.end());
}

template<typename _RD>
int Discrete::gen(_RD& rd) {
  return values[dist(rd)];
}

int Discrete::gen() {
  return gen(engine);
//  //custom implementation 
//  double u = (double)rand() / RAND_MAX;
//  int x=0;
//  for (; x < weights.size() && u>=0; x++) {
//    u -= weights[x];
//  }
//  x--;
//  return values[x];
}

double Discrete::likeli(const int& x) {
  if (x >= 0 && x < weights.size())
    return weights[x];
  else
    return 0;
}

double Discrete::loglikeli(const int& x) {
  // todo: check -infinity!!!
  if (x >= 0 && x < weights.size())
    return log_weights[x];
  else
    return - INFINITY;
}

} /* namespace random */
} /* namespace swift */
