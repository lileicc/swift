/*
 * Gamma.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Gamma.h"

namespace swift {
namespace random {

Gamma::Gamma() :
  dist(1.0, 1.0), alpha(1.0), beta(1.0),
  is_like_ok(false), is_loglike_ok(false) {
}

Gamma::~Gamma() {
}

void Gamma::init(double alpha, double beta) {
  this->alpha = alpha;
  this->beta = beta;
  dist = std::gamma_distribution<double>(alpha,beta);
  is_like_ok = false;
  is_loglike_ok = false;
}

double Gamma::gen() {
  return dist(engine);
}

double Gamma::likeli(const double& x) {
  if(!is_like_ok) {
    coef = 1.0 / (std::tgamma(alpha) * std::pow(beta, alpha));
    inv_beta = 1.0 / beta;
    is_like_ok = true;
  }
  return coef * std::pow(x, alpha - 1) * exp(-x * inv_beta);
}

double Gamma::loglikeli(const double& x) {
  if(!is_loglike_ok) {
    log_coef = -std::lgamma(alpha)-alpha*std::log(beta);
    inv_beta = 1.0 / beta;
    is_loglike_ok = true;
  }
  return log_coef + (alpha-1) * std::log(x) - inv_beta * x;
}

} /* namespace random */
} /* namespace swift */

