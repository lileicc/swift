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

template<typename T>
class SwiftDistribution {
public:
  SwiftDistribution() {
  }
  ;
  virtual ~SwiftDistribution() {
  }
  ;

  virtual T gen() = 0; // generate a sample from this distribution
  virtual double likeli(const T& x) = 0; // calculate the likelihood
  virtual double loglikeli(const T& x) = 0; // calculate the log-likelihood
protected:
  static std::default_random_engine engine;
  const long double PI = 3.141592653589793238L;
};

//template<typename T>
//std::default_random_engine SwiftDistribution<T>::engine(0);
template <typename T>
std::default_random_engine SwiftDistribution<T>::engine = std::default_random_engine((unsigned) std::chrono::system_clock::now().time_since_epoch().count());

} /* namespace random */
} /* namespace swift */
