/*
 * SwiftDistribution.h
 *
 *  Created on: Nov 22, 2013
 *      Author: leili
 */

#pragma once

namespace swift {
namespace random {

template <typename T>
class SwiftDistribution {
public:
  SwiftDistribution();
  virtual ~SwiftDistribution();

  virtual T gen(); // generate a sample from this distribution
  virtual double likeli(T x); // calculate the likelihood
  virtual double loglikeli(T x); // calculate the log-likelihood
};

} /* namespace random */
} /* namespace swift */
