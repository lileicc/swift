/*
 * InvWishart.h
 *
 *  Created on: July 11, 2016 
 *      Author: giulio-zhou
 */
#pragma once
#include<random>
#include "Gamma.h"
#include "MultivarGaussian.h"
#include "SwiftDistribution.h"

#include "armadillo"

namespace swift {
namespace random {

class InvWishart: public swift::random::SwiftDistribution<arma::mat> {
public:
  InvWishart();
  virtual ~InvWishart();
  void init(const arma::mat& scale, int freeDeg);
  double likeli(const arma::mat& x);
  double loglikeli(const arma::mat& x);
  arma::mat gen();
private:
  arma::mat retvec;
  arma::mat scale;
  int freeDeg;
  double multivarGamma(int p, double x);
  double logMultivarGamma(int p, double x);
  int d;
  double dimFactor, logDimFactor, normConst, logNormConst;
  MultivarGaussian mvg;
  Gamma g;
  bool is_gen_ok, is_likeli_ok, is_loglikeli_ok;
};

} /* namespace random */
} /* namespace swift */
