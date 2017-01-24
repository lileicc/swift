/*
 * Laplace.h
 *
 *  Created on: Feb 25, 2016
 *      Author: nishdesai
 */
 #pragma once
 #include <random>
 #include "SwiftDistribution.h"

 namespace swift {
 namespace random {

 class Laplace: public swift::random::SwiftDistribution<double> {
 public:
   Laplace();
   virtual ~Laplace();
   void init(double mu = 0.0, double b = 1);
   double gen();
   double likeli(const double& x);
   double loglikeli(const double& x);
 private:
   std::uniform_real_distribution<double> dist;
   double mu, b, log_b;
   bool is_loglike_ok;
 };

 } /* namespace random */
 } /* namespace swift */
