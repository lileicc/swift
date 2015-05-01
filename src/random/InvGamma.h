/*
 * InvGamma.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class InvGamma: public swift::random::SwiftDistribution<double> {
public:
  InvGamma();
  virtual ~InvGamma();
  void init(double alpha = 1.0, double beta = 1.0);
  double gen();
  double likeli(const double& x);
  double loglikeli(const double& x);
private:
  std::gamma_distribution<double> dist;
  double alpha, beta, inv_beta;
  double coef, log_coef;
  bool is_like_ok, is_loglike_ok;
};

} /* namespace random */
} /* namespace swift */

