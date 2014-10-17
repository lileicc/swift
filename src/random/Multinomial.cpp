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
  n = 1;
  for (size_t i = 1; i < weight.size(); ++ i)
    weight[i] += weight[i - 1];
  sum_wei = weight.back();
  is_logwei_ok.clear();
}

void Multinomial::init(int n, const std::vector<double>& wei) {
  this->init(wei);
  this->n = n;
}

void Multinomial::init(const double* begin, const double* end) {
  weight.clear();
  sum_wei = 0;
  for (const double* ptr = begin; ptr != end; ++ ptr)
    weight.push_back(sum_wei += *ptr);
  n = 1;
  is_logwei_ok.clear();
}

void Multinomial::init(const arma::mat& wei) {
  init(wei.memptr(), wei.memptr() + wei.n_elem);
}

void Multinomial::init(int n, const arma::mat& wei) {
  init(wei.memptr(), wei.memptr() + wei.n_elem);
  this->n = n;
}

std::vector<int> Multinomial::gen() {
  if (n > 3 * weight.size())
    return gen_large(n);
  else 
  if (n * 20 < weight.size())
    return gen_small(n);
  else
    return gen_medium(n);
}

std::vector<int> Multinomial::gen_medium(int n) {
  tmp_keys.resize(n);
  for (int i = 0; i < n; ++ i)
    tmp_keys[i] = dist(engine) * sum_wei;
  std::sort(tmp_keys.begin(), tmp_keys.end());
  std::vector<int> ret(weight.size(), 0);
  int ptr = 0;
  for (auto& k : tmp_keys) {
    while (weight[ptr] < k) ++ ptr;
    ret[ptr] ++;
  }
  return ret;
}

std::vector<int> Multinomial::gen_small(int n) {
  std::vector<int> ret(weight.size(), 0);
  for(int i=0;i<n;++i){
    double w = dist(engine) * sum_wei;
    ret[lower_bound(weight.begin(), weight.end(), w) - weight.begin()] ++;
  }
  return ret;
}

std::vector<int> Multinomial::gen_large(int n) {
  std::vector<int> ret(weight.size(), 0);
  int prev_n = 0;
  double prev_w = 0;
  std::size_t k = weight.size();
  for (int i = 0; i < k - 1 && prev_n < n; ++i) {
    std::binomial_distribution<int> binom(n - prev_n, weight[i] / (sum_wei - prev_w));
    prev_w += weight[i];
    prev_n += (ret[i] = binom(engine));
  }
  if (k > 0) {
    ret[k - 1] = n - prev_n;
  }
  return ret;
}

double Multinomial::likeli(const std::vector<int>& x) {
  if (x.size() != weight.size()) return 0;
  double ret = 1;
  for (size_t i = 0; i < x.size(); ++i) {
    if (x[i] > 0) {
      double w = (!i ? weight[0] : weight[i] - weight[i - 1]);
      ret *= std::pow(w, x[i]);
    }
  }
  return ret;
}

double Multinomial::loglikeli(const std::vector<int>& x) {
  if (x.size() != weight.size()) return -INFINITY;
  if(is_logwei_ok.size() == 0) {
    is_logwei_ok.resize(x.size());
    log_weight.resize(x.size());
  }
  double ret = 0;
  for(size_t i = 0; i < x.size(); ++ i) {
    if (x[i]<=0) continue;
    if(is_logwei_ok[i])
      ret += log_weight[i] * x[i];
    else {
      is_logwei_ok[i] = true;
      ret += 
      x[i] * (log_weight[i] = 
      std::log(i == 0 ? weight[0] : weight[i] - weight[i-1]));
    }
  }
  return ret;
}

} /* namespace random */
} /* namespace swift */

