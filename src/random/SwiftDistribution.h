/*
 * SwiftDistribution.h
 *
 *  Created on: Nov 22, 2013
 *      Author: leili
 */

#pragma once
#include <random>
#include <chrono>

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
  static std::default_random_engine engine;
};

  
template <typename T>
  std::default_random_engine SwiftDistribution<T>::engine = std::default_random_engine((unsigned) std::chrono::system_clock::now().time_since_epoch().count());
  
  
} /* namespace random */
} /* namespace swift */
