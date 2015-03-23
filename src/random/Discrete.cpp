/*
 * Discrete.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: yiwu
 */
#include <numeric>
#include <cmath>
#include "Discrete.h"

namespace swift {
namespace random {

Discrete::Discrete()
  :is_dist_ok(false) {
}

Discrete::~Discrete() {
}

void Discrete::init(const std::vector<double>& wei) {
  weights = wei;
  is_dist_ok = false;
  is_logwei_ok.clear();
}

void Discrete::init(const arma::mat& wei) {
  weights.resize(wei.n_elem);
  for (size_t i = 0; i < wei.n_elem; ++ i)
    weights[i] = wei[i];
  is_dist_ok = false;
  is_logwei_ok.clear();
}

template<typename _RD>
int Discrete::gen(_RD& rd) {
  return dist(rd);
}

int Discrete::gen() {
  if(!is_dist_ok) {
    /*
     Note: In VS2013, we have to rewrite the last line with the following code
     
    auto lis = std::initializer_list<double>(weights.data(), weights.data() + weights.size());
    dist = std::discrete_distribution<int>(lis);
     */
    dist = std::discrete_distribution<int>(weights.begin(), weights.end());
    is_dist_ok = true;
  }
  return gen(engine);
//  //custom implementation 
//  double u = (double)rand() / RAND_MAX;
//  int x=0;
//  for (; x < weights.size() && u>=0; x++) {
//    u -= weights[x];
//  }
//  x--;
//  return values[x];
}

double Discrete::likeli(const int& x) {
  if (x >= 0 && x < weights.size())
    return weights[x];
  else
    return 0;
}

double Discrete::loglikeli(const int& x) {
  // todo: check -infinity!!!
  if (x >= 0 && x < weights.size()) {
    if(is_logwei_ok.size() == 0) {
      is_logwei_ok.resize(weights.size());
      log_weights.resize(weights.size());
    }
    if(!is_logwei_ok[x]) {
      log_weights[x] = std::log(weights[x]);
      is_logwei_ok[x]=true;
    }
    return log_weights[x];
  } else
    return - INFINITY;
}

} /* namespace random */
} /* namespace swift */
