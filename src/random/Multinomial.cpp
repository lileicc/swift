/*
 * Multinomial.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include <algorithm>
#include "Multinomial.h"

namespace swift {
namespace random {

Multinomial::Multinomial() : dist(0, 1.0) {
}

Multinomial::~Multinomial() {
}

void Multinomial::init(const std::vector<double>& wei) {
  weight = wei;
  for (size_t i = 1; i < weight.size(); ++ i)
    weight[i] += weight[i - 1];
  sum_wei = weight.back();
  is_logwei_ok.clear();
}

void Multinomial::init(const double* wei, int n) {
  init(wei, wei + n);
}

void Multinomial::init(const double* begin, const double* end) {
  weight.clear();
  sum_wei = 0;
  for (const double* ptr = begin; ptr != end; ++ ptr)
    weight.push_back(sum_wei += *ptr);
  is_logwei_ok.clear();
}

void Multinomial::init(const arma::mat& wei) {
  init(wei.memptr(), wei.memptr() + wei.n_elem);
}

int Multinomial::gen() {
  return std::lower_bound(weight.begin(), weight.end(), dist(engine) * sum_wei)
              - weight.begin();
}

std::vector<int> Multinomial::gen(int n) {
  std::vector<double> key;
  for (int i = 0; i < n; ++ i)
    key.push_back(dist(engine) * sum_wei);
  std::sort(key.begin(), key.end());
  std::vector<int> ret;
  int ptr = 0;
  for (auto& k : key) {
    while (weight[ptr] < k) ++ ptr;
    ret.push_back(ptr);
  }
  return ret;
}

double Multinomial::likeli(const int& x) {
  if (x == 0) return weight[x];
  if (x >= weight.size()) return 0;
  return weight[x] - weight[x - 1];
}

double Multinomial::loglikeli(const int& x) {
  if(is_logwei_ok.size() == 0) {
    is_logwei_ok.resize(weight.size());
    log_weight.resize(weight.size());
  }
  if(is_logwei_ok[x])
    return log_weight[x];
  else {
    is_logwei_ok[x] = true;
    return (log_weight[x] = 
            std::log(x == 0 ? weight[0] 
                    : weight[x] - weight[x-1]));
  }
}

double Multinomial::likeli(const std::vector<int>& x) {
  double ret = 1;
  for (auto& v : x) 
    ret *= likeli(v);
  return ret;
}
double Multinomial::loglikeli(const std::vector<int>& x) {
  if(is_logwei_ok.size() == 0) {
    is_logwei_ok.resize(x.size());
    log_weight.resize(x.size());
  }
  double ret = 0;
  for(auto& v : x) {
    if(is_logwei_ok[v])
      ret += log_weight[v];
    else {
      is_logwei_ok[v] = true;
      ret += 
      (log_weight[v] = 
      std::log(v == 0 ? weight[0] : weight[v] - weight[v-1]));
    }
  }
  return ret;
}

} /* namespace random */
} /* namespace swift */
