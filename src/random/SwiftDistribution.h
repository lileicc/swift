/*
 * SwiftDistribution.h
 *
 *  Created on: Nov 22, 2013
 *      Author: leili
 */

#pragma once

#include <random>

namespace swift {
namespace random {

template <typename T>
class SwiftDistribution {
public:
  SwiftDistribution() {};
  virtual ~SwiftDistribution() {};

  virtual T gen() = 0; // generate a sample from this distribution
  virtual double likeli(T x) = 0; // calculate the likelihood
  virtual double loglikeli(T x) = 0; // calculate the log-likelihood

protected:
  std::default_random_engine engine;
};

} /* namespace random */
} /* namespace swift */
