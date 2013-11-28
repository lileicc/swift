/*
 * CategoricalDistribution.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CategoricalDistribution.h"

namespace swift {
namespace random {

CategoricalDistribution::CategoricalDistribution() {
}

CategoricalDistribution::~CategoricalDistribution() {
}

void CategoricalDistribution::init(std::map<int, double>& weights) {
  for (auto it : weights) {
    keys.push_back( it.first);
    ws.push_back(it.second);
  }
  dist = std::discrete_distribution<int>(ws.begin(), ws.end());
}

int CategoricalDistribution::gen() {
  return dist();
}

double CategoricalDistribution::likeli(int x) {
  return (x>=0)? ws[x]: 0;
}

double CategoricalDistribution::loglikeli(int x) {
  return log(likeli(x));
}

} /* namespace random */
} /* namespace swift */
