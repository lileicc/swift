/*
 * Dirichlet.h
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Dirichlet.h"

namespace swift {
namespace random {

Dirichlet::Dirichlet() {
}

Dirichlet::~Dirichlet() {
}

void Dirichlet::init(std::vector<double> alpha) {
  this->alpha = alpha;
  dist_alpha.clear();
  double alpha_sum = 0;
  coef = 1;
  log_coef = 0;
  for(auto a: alpha) {
  	dist_alpha.push_back(std::gamma_distribution<double>(a));
  	alpha_sum += a;
  	coef *= 1.0 / std::tgamma(a);
  	log_coef -= std::lgamma(a);
  }
  coef *= std::tgamma(alpha_sum);
  log_coef += std::lgamma(alpha_sum);
}

std::vector<double> Dirichlet::gen() {
  std::vector<double> x;
  double sum = 0;
  for(auto dist: dist_alpha) {
    x.push_back(dist(engine));
    sum += x.back();
  }
  for(size_t i = 0; i < x.size(); ++ i)
    x[i] /= sum;
  return x;
}

double Dirichlet::likeli(std::vector<double> x) {
  if(x.size() != alpha.size()) return 0;
  double ret = coef;
  for(size_t i = 0; i < alpha.size(); ++ i)
    ret*= pow(x[i], alpha[i] - 1.0);
  return ret;
}

double Dirichlet::loglikeli(std::vector<double> x) {
  if(x.size() != alpha.size()) return - INFINITY;
  double ret = - log_coef;
  for(size_t i = 0; i < alpha.size(); ++ i)
    ret -= (alpha[i] - 1.0) * x[i];
  return ret;
}

} /* namespace random */
} /* namespace swift */
