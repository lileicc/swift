/*
 * UniformVector.h
 *
 *  Created on: Mar 16, 2014
 *      Author: yiwu
 */

#pragma once
#include <random>
#include <vector>
#include "SwiftDistribution.h"

#include "armadillo"

namespace swift {
namespace random {

class UniformVector: public swift::random::SwiftDistribution<arma::mat> {
public:
  UniformVector();
  virtual ~UniformVector();
  void init(const arma::mat& box);
  void init(const arma::mat& lo, const arma::mat& hi);
  arma::mat gen();
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);
private:
  std::uniform_real_distribution<double> dist;
  std::vector<double> a;
  std::vector<double> b;
  double prod, logprod;
  arma::mat retvec;
  bool is_prod_ok, is_logprod_ok;
};

} /* namespace random */
} /* namespace swift */
