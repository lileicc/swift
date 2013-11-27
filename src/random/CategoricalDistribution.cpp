/*
 * CategoricalDistribution.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CategoricalDistribution.h"

namespace swift {
namespace random {

CategoricalDistribution::CategoricalDistribution(std::initializer_list<double> il) : dist(il) {
}

CategoricalDistribution::~CategoricalDistribution() {
  // TODO Auto-generated destructor stub
}

} /* namespace random */
} /* namespace swift */
