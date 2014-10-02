/*
 * Multinomial.h
 *
 *  Created on: Feb 28, 2014
 *      Author: yiwu
 */

#pragma once
#include <cstdarg>
#include <random>
#include <vector>
#include "SwiftDistribution.h"

namespace swift {
namespace random {

class Multinomial: public swift::random::SwiftDistribution<int > {
public:
  Multinomial();
  virtual ~Multinomial();
  void init(std::vector<double> wei);
  void init(double* wei, int n);
  void init(double* begin, double* end);
  int gen();
  std::vector<int> gen(int n);
  double likeli(const int& x);
  double loglikeli(const int& x);
  double likeli(const std::vector<int>& x);
  double loglikeli(const std::vector<int>& x);
private:
  std::uniform_real_distribution<double> dist;
  std::vector<double> weight;
};

} /* namespace random */
} /* namespace swift */
