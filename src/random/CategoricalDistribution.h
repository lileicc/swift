/*
 * CategoricalDistribution.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <initializer_list>
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class CategoricalDistribution: public swift::random::SwiftDistribution<int> {
public:
  CategoricalDistribution(std::initializer_list<double> il);
  ~CategoricalDistribution();
private:
  std::discrete_distribution dist;
};

} /* namespace random */
} /* namespace swift */
