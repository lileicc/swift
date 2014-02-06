/*
 * BetaDistribution.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "BetaDistribution.h"

namespace swift {
namespace random {

BetaDistribution::BetaDistribution() :
    alpha(2.0), beta(2.0) {
  coef = std::tgamma((long double)(alpha + beta)) * 
  	(1.0L / std::tgamma((long double)alpha)) * (1.0L / std::tgamma((long double)beta));
  log_coef = std::lgamma((long double)(alpha+beta)) - std::lgamma((long double)alpha) - std::lgamma((long double)beta);
}

BetaDistribution::~BetaDistribution() {
}

void BetaDistribution::init(double alpha, double beta) {
  this->alpha = alpha;
  this->beta = beta;
  dist_alpha = std::gamma_distribution<double>(alpha);
  dist_beta = std::gamma_distribution<double>(beta);
}

double BetaDistribution::gen() {
  double x = dist_alpha(engine);
  return x / (x + dist_beta(engine));
}

double BetaDistribution::likeli(double x) {
  return coef * pow(x, alpha - 1.0) * pow(1.0 - x, beta - 1.0);
}

double BetaDistribution::loglikeli(double x) {
  return - (log_coef + (alpha - 1.0) * x + (beta - 1.0) * (1.0 - x));
}

} /* namespace random */
} /* namespace swift */
