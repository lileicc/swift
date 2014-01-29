/*
 * CategoricalDistribution.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */
#include <numeric>
#include <cmath>
#include "CategoricalDistribution.h"

namespace swift {
namespace random {

Categorical::Categorical() {
//  srand(time(NULL));
}

Categorical::~Categorical() {
}

void Categorical::init(const std::map<int, double>& ws) {
  values.clear();
  weights.clear();
  values_to_indic.clear();
  int i = 0;
  for (auto it : ws) {
    if (it.second > 0 && it.second <= 1) {
      values.push_back(it.first);
      weights.push_back(it.second);
      values_to_indic[it.first] = i;
      log_weights.push_back(std::log(it.second));
      i++;
    }
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
int Categorical::gen(_RD& rd) {
  return values[dist(rd)];
}

int Categorical::gen() {
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

double Categorical::likeli(int x) {
  auto e = values_to_indic.find(x);
  if (e != values_to_indic.end())
    x = e->second;
  else
    return 0;
  return weights[x];
}

double Categorical::loglikeli(int x) {
  // todo: check -infinity!!!
  auto e = values_to_indic.find(x);
  if (e != values_to_indic.end())
    x = e->second;
  else
    return - INFINITY;
  return log_weights[x];
}

} /* namespace random */
} /* namespace swift */
