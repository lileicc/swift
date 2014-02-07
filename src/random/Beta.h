/*
 * Beta.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Beta: public swift::random::SwiftDistribution<double> {
public:
  Beta();
  virtual ~Beta();
  void init(double alpha = 2.0, double beta = 2.0);
  double gen();
  double likeli(double x);
  double loglikeli(double x);
private:
  std::gamma_distribution<double> dist_alpha, dist_beta;
  double alpha, beta;
  double coef, log_coef;
};

} /* namespace random */
} /* namespace swift */
