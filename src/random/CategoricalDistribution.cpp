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

CategoricalDistribution::CategoricalDistribution(std::initializer_list<double> il)
  : dist(il), weight(il) {
  // TODO Auto-generated constructor stub
    double total_weight = std::accumulate(weight.begin(), weight.end(), 0.0);
    if (total_weight >= 1.0) {
      for (size_t i = 0; i<weight.size(); ++i)
        weight[i] /= total_weight;
      total_weight = 1;
      has_null = 0;
    }
    else {
      has_null = 1;
      weight.insert(weight.begin(), 1.0 - total_weight);
    }
}

CategoricalDistribution::~CategoricalDistribution() {
  // TODO Auto-generated destructor stub
}

int CategoricalDistribution::gen() {
  return dist(engine) - has_null;
}

double CategoricalDistribution::likeli(int x) {
  x += has_null;
  if(x<0 || x>=(int)weight.size()) return 0;
  return weight[x];
}

double CategoricalDistribution::loglikeli(int x) {
  return log(likeli(x));
}

} /* namespace random */
} /* namespace swift */
