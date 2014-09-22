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
using namespace arma;

namespace swift {
namespace random {

class UniformVector: public swift::random::SwiftDistribution<mat> {
public:
  UniformVector();
  virtual ~UniformVector();
  void init(mat box);
  void init(mat lo, mat hi);
  mat gen();
  double likeli(const mat& x);
  double loglikeli(const mat& x);
private:
  std::vector<std::uniform_real_distribution<double>> dists;
  std::vector<double> a;
  std::vector<double> b;
  double prod, logprod;
  mat retvec;
};

} /* namespace random */
} /* namespace swift */
