/*
 * Dirichlet.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Dirichlet.h"

namespace swift {
namespace random {

Dirichlet::Dirichlet() :
  is_coef_ok(false), is_logcoef_ok(false),
  is_dist_ok(false) {
}

Dirichlet::~Dirichlet() {
}

void Dirichlet::init(std::vector<double> alpha) {
  this->alpha = alpha;
  is_dist_ok = false;
  is_coef_ok = false;
  is_logcoef_ok = false;
}

void Dirichlet::init(arma::mat alpha) {
  std::vector<double> vec(alpha.n_elem);
  for (size_t i = 0; i < alpha.n_elem; ++ i)
    vec.push_back(alpha[i]);
  init(vec);
}

void Dirichlet::init(int n_param, ...) {
  va_list args;
  va_start(args, n_param);
  std::vector<double> vec_args;
  for (int i = 0; i < n_param; ++i) {
    vec_args.push_back(va_arg(args, double));
  }
  va_end(args);
  init(vec_args);
}

arma::mat Dirichlet::gen() {
  if(!is_dist_ok){
    arr.reshape(1, (int)alpha.size());
    dist_alpha.resize(alpha.size());
    auto iter = dist_alpha.begin();
    for(auto&a:alpha) {
      *iter++ = std::gamma_distribution<double>(a);
    }
    is_dist_ok = true;
  }
  int i = 0;
  double sum = 0;
  for(auto dist: dist_alpha) {
    sum += (arr[i++] = dist(engine));
  }
  arr /= sum;
  return arr;
}

double Dirichlet::likeli(const arma::mat& x) {
  if(x.n_elem != alpha.size()) return 0;
  if(!is_coef_ok) {
    double alpha_sum = 0;
    coef = 1;
    for(auto& a: alpha) {
    	alpha_sum += a;
    	coef *= 1.0/std::tgamma(a);
    }
    coef *= std::tgamma(alpha_sum);
    is_coef_ok = true;
  }
  double ret = coef;
  for(size_t i = 0; i < alpha.size(); ++ i)
    ret*= pow(x[i], alpha[i] - 1.0);
  return ret;
}

double Dirichlet::loglikeli(const arma::mat& x) {
  if(x.n_elem != alpha.size()) return - INFINITY;
  if(!is_logcoef_ok) {
    double alpha_sum = 0;
    log_coef = 0;
    for(auto a: alpha) {
    	alpha_sum += a;
    	log_coef -= std::lgamma(a);
    }
    log_coef += std::lgamma(alpha_sum);
    is_logcoef_ok = true;
  }
  double ret = log_coef;
  for(size_t i = 0; i < alpha.size(); ++ i)
    ret += (alpha[i] - 1.0) * x[i];
  return ret;
}

} /* namespace random */
} /* namespace swift */
