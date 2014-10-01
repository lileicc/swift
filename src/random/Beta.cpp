/*
 * Beta.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Beta.h"

namespace swift {
namespace random {

Beta::Beta() :
    alpha(2.0), beta(2.0),
    is_dist_ok(false), is_like_ok(false), is_loglike_ok(false) {
}

Beta::~Beta() {
}

void Beta::init(double alpha, double beta) {
  this->alpha = alpha;
  this->beta = beta;
  is_dist_ok = false;
  is_like_ok = false;
  is_loglike_ok = false;
}

double Beta::gen() {
  if(!is_dist_ok) {
    dist_alpha = std::gamma_distribution<double>(alpha);
    dist_beta = std::gamma_distribution<double>(beta);    
    is_dist_ok = true;
  }
  double x = dist_alpha(engine);
  return x / (x + dist_beta(engine));
}

double Beta::likeli(const double& x) {
  if(!is_like_ok){
    coef = std::tgammal((long double)(alpha + beta)) *
      (1.0L / std::tgammal((long double)alpha)) * (1.0L / std::tgammal((long double)beta));
    is_like_ok = true;
  }
  return coef * pow(x, alpha - 1.0) * pow(1.0 - x, beta - 1.0);
}

double Beta::loglikeli(const double& x) {
  if(!is_loglike_ok){
    log_coef = std::lgammal((long double)(alpha+beta)) 
      - std::lgammal((long double)alpha) - std::lgammal((long double)beta);
    is_loglike_ok = true;
  }
  return log_coef + (alpha - 1.0) * x + (beta - 1.0) * (1.0 - x);
}

} /* namespace random */
} /* namespace swift */
