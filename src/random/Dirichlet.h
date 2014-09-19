/*
 * Dirichlet.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */

#pragma once
#include <cstdarg>
#include <random>
#include <vector>
#include "SwiftDistribution.h"

#include "armadillo"
using namespace arma;

namespace swift {
namespace random {

class Dirichlet: public swift::random::SwiftDistribution<mat> {
public:
  Dirichlet();
  virtual ~Dirichlet();
  void init(mat alpha);
  void init(std::vector<double> alpha);
  void init(int n_param, ...);
  mat gen();
  double likeli(const mat& x);
  double loglikeli(const mat& x);
private:
  std::vector<std::gamma_distribution<double> > dist_alpha;
  std::vector<double> alpha;
  mat arr;
  double coef, log_coef;
};

} /* namespace random */
} /* namespace swift */
