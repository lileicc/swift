/*
 * Beta.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Beta.h"

namespace swift {
namespace random {

Beta::Beta() :
    alpha(2.0), beta(2.0) {
}

Beta::~Beta() {
}

void Beta::init(double alpha, double beta) {
  this->alpha = alpha;
  this->beta = beta;
  coef = std::tgammal((long double)(alpha + beta)) *
  (1.0L / std::tgammal((long double)alpha)) * (1.0L / std::tgammal((long double)beta));
  log_coef = std::lgammal((long double)(alpha+beta)) - std::lgammal((long double)alpha) - std::lgammal((long double)beta);
  dist_alpha = std::gamma_distribution<double>(alpha);
  dist_beta = std::gamma_distribution<double>(beta);
}

double Beta::gen() {
  double x = dist_alpha(engine);
  return x / (x + dist_beta(engine));
}

double Beta::likeli(double x) {
  return coef * pow(x, alpha - 1.0) * pow(1.0 - x, beta - 1.0);
}

double Beta::loglikeli(double x) {
  return - (log_coef + (alpha - 1.0) * x + (beta - 1.0) * (1.0 - x));
}

} /* namespace random */
} /* namespace swift */
