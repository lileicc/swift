/*
 * CategoricalDistribution.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CategoricalDistribution.h"

#include <cmath>
#include <numeric>
#include "SwiftDistribution.cpp"

namespace swift {
namespace random {

CategoricalDistribution::CategoricalDistribution() {
}

CategoricalDistribution::~CategoricalDistribution() {
}

void CategoricalDistribution::init(std::map<int, double>& weights) {
  for (auto it : weights) {
    keys.push_back(it.first);
    weight.push_back(it.second);
  }
  /*
  Note: In VS2013, we have to rewrite the last line with the following code

  double* A = new double[weight.size()];
  for (int i = 0; i<weight.size(); ++i)A[i] = weight[i];
  auto lis = std::initializer_list<double>(A, A + weight.size());
  dist = std::discrete_distribution<int>(lis);
  delete[weight.size()] A;
  */
  dist = std::discrete_distribution<int>(weight.begin(), weight.end());
}

template <typename _RD>
int CategoricalDistribution::gen(_RD& rd) {
  return dist(engine);
}

double CategoricalDistribution::likeli(int x) {
  if(x<0 || x>=(int)weight.size()) return 0;
  return weight[x];
}

double CategoricalDistribution::loglikeli(int x) {
  return log(likeli(x));
}

} /* namespace random */
} /* namespace swift */
