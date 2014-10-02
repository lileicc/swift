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

namespace swift {
namespace random {

class Dirichlet: public swift::random::SwiftDistribution<arma::mat> {
public:
  Dirichlet();
  virtual ~Dirichlet();
  void init(arma::mat alpha);
  void init(std::vector<double> alpha);
  void init(int n_param, ...);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);
private:
  std::vector<std::gamma_distribution<double> > dist_alpha;
  std::vector<double> alpha;
  arma::mat arr;
  double coef, log_coef;
  bool is_coef_ok, is_logcoef_ok, is_dist_ok;
};

} /* namespace random */
} /* namespace swift */
