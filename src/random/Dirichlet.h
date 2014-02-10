/*
 * Beta.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include <vector>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Dirichlet: public swift::random::SwiftDistribution<std::vector<double> > {
public:
  Dirichlet();
  virtual ~Dirichlet();
  void init(std::vector<double> alpha);
  std::vector<double> gen();
  double likeli(const std::vector<double>& x);
  double loglikeli(const std::vector<double>& x);
private:
  std::vector<std::gamma_distribution<double> > dist_alpha;
  std::vector<double> alpha;
  double coef, log_coef;
};

} /* namespace random */
} /* namespace swift */
