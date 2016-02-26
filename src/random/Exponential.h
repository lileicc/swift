/*
 * Exponential.h
 *
 *  Created on: Feb 25, 2016
 *      Author: nishdesai
 */
 #pragma once
 #include <random>
 #include "SwiftDistribution.h"

 namespace swift {
 namespace random {

 class Exponential: public swift::random::SwiftDistribution<double> {
 public:
   Exponential();
   virtual ~Exponential();
   void init(double lambda = 1.0);
   double gen();
   double likeli(const double& x);
   double loglikeli(const double& x);
 private:
   std::exponential_distribution<double> dist;
   double lambda, log_lambda;
   bool is_like_ok, is_loglike_ok;
 };

 } /* namespace random */
 } /* namespace swift */
