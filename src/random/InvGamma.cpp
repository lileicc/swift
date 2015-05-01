/*
 * InvGamma.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "InvGamma.h"

namespace swift {
namespace random {

InvGamma::InvGamma() :
  dist(1.0, 1.0), alpha(1.0), beta(1.0),
  is_like_ok(false), is_loglike_ok(false) {
}

InvGamma::~InvGamma() {
}

void InvGamma::init(double alpha, double beta) {
  beta = 1.0 / beta;
  this->alpha = alpha;
  this->beta = beta;
  dist = std::gamma_distribution<double>(alpha,beta);
  is_like_ok = false;
  is_loglike_ok = false;
}

double InvGamma::gen() {
  return 1.0 / dist(engine);
}

double InvGamma::likeli(const double& x) {
  if(!is_like_ok) {
    coef = 1.0 / (std::tgamma(alpha) * std::pow(beta, alpha));
    inv_beta = 1.0 / beta;
    is_like_ok = true;
  }
  return coef * std::pow(1.0 / x, alpha - 1) * exp(-1.0 / x * inv_beta);
}

double InvGamma::loglikeli(const double& x) {
  if(!is_loglike_ok) {
    log_coef = -std::lgamma(alpha)-alpha*std::log(beta);
    inv_beta = 1.0 / beta;
    is_loglike_ok = true;
  }
  return log_coef - (alpha-1) * std::log(x) - inv_beta / x;
}

} /* namespace random */
} /* namespace swift */

