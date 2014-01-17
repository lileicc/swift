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
}

Categorical::~Categorical() {
}

void Categorical::init(const std::map<int, double>& ws) {
  values.clear();
  weights.clear();
  values_to_indic.clear();
  for (auto it : ws) {
    if (it.second > 0 && it.second <= 1) {
      values.push_back(it.first);
      weights.push_back(it.second);
      log_weights.push_back(log(it.second));
    }
  }
  /*
  Note: In VS2013, we have to rewrite the last line with the following code

  double* A = new double[weight.size()];
  for (int i = 0; i<weight.size(); ++i)A[i] = weight[i];
  auto lis = std::initializer_list<double>(A, A + weight.size());
  dist = std::discrete_distribution<int>(lis);
  delete[weight.size()] A;
  */
  dist = std::discrete_distribution<int>(weights.begin(), weights.end());
}

template <typename _RD>
int Categorical::gen(_RD& rd) {
  return values[dist(rd)];
}
  
int Categorical::gen(){
  return gen(engine);
}

double Categorical::likeli(int x) {
  auto e = values_to_indic.find(x);
  if (e!=values_to_indic.end())
    x = e->second;
  else return 0;
  return weights[x];
}

double Categorical::loglikeli(int x) {
  // todo: check -infinity!!!
  auto e = values_to_indic.find(x);
  if (e!=values_to_indic.end())
    x = e->second;
  else return 0;
  return log_weights[x];
}

} /* namespace random */
} /* namespace swift */
