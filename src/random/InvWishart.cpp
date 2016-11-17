/*
 * InvWishart.cpp
 *
 *   Created on: July 11, 2016
 *       Author: giulio-zhou
 */

#include <cmath>
#include <cassert>
#include "InvWishart.h"

namespace swift {
namespace random {

InvWishart::InvWishart()
  : is_gen_ok(false), is_likeli_ok(false), is_loglikeli_ok(false) {
}

InvWishart::~InvWishart() {
}

void InvWishart::init(const arma::mat& _scale, int _freeDeg) {
  scale = _scale; 
  freeDeg = _freeDeg;
  d = scale.n_rows;

  // Dimension check
  assert(scale.n_rows == scale.n_cols);
  assert(freeDeg > d - 1);

  is_gen_ok = false;
  is_likeli_ok = false;
  is_loglikeli_ok = false;

  g.init(d);
}

double InvWishart::likeli(const arma::mat& x) {
  if (!is_likeli_ok) {
    dimFactor = 1 / (pow(2, freeDeg * d * 0.5) *
                     multivarGamma(d, freeDeg * 0.5));
    normConst = pow(arma::det(scale), freeDeg * 0.5) * dimFactor;
    is_likeli_ok = true;
  }

  return normConst * pow(arma::det(x), -(freeDeg + d + 1) * 0.5) *
         exp(-0.5 * arma::trace(scale * arma::inv_sympd(x)));
}

double InvWishart::loglikeli(const arma::mat& x) {
  if (!is_loglikeli_ok) {
    logDimFactor = -log(2) * freeDeg * d * 0.5 -
                   logMultivarGamma(d, freeDeg * 0.5);
    logNormConst = std::log(arma::det(scale)) * 0.5 + logDimFactor;
    is_loglikeli_ok = true; 
  }
  return logNormConst - ((freeDeg + d + 1) * 0.5 * std::log(arma::det(x)))
                      - 0.5 * arma::trace(scale * arma::inv_sympd(x));
}

arma::mat InvWishart::gen() {
  if (!is_gen_ok) {
    retvec.set_size(d, d);
    mvg.init(arma::zeros<arma::mat>(d, 1), arma::inv_sympd(scale));
    is_gen_ok = true;
  }

  arma::vec s;
  do {
    retvec.zeros();
    for (int i = 0; i < freeDeg; i++) {
      arma::mat temp = mvg.gen();
      retvec += temp * temp.t();
    }
    s = arma::svd(retvec);
  } while (s[0] > 1e3 * s[d - 1]);

  return arma::inv_sympd(retvec);
}

double InvWishart::multivarGamma(int p, double x) {
  return exp(logMultivarGamma(p, x));
}

double InvWishart::logMultivarGamma(int p, double x) {
  double ret = logPI * p * (p - 1) * 0.25;
  for (int i = 1; i <= p; i++) {
    ret += g.loglikeli(x + (1 - i) * 0.5);
  }
  return ret;
}

} /* namespace random */
} /* namespace swift */
