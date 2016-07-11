/*
 * Multinomial.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include <algorithm>
#include <numeric>
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
  sum_wei = std::accumulate(wei.begin(), wei.end(), 0.0);
  is_logwei_ok.clear();
}

void Multinomial::init(int n, const std::vector<double>& wei) {
  this->init(wei);
  this->n = n;
}

void Multinomial::init(const double* begin, const double* end) {
  weight.resize(end - begin);
  sum_wei = 0;
  int i = 0;
  for (const double* ptr = begin; ptr != end; ptr ++)
    sum_wei += (weight[i++] = *ptr);
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
    return gen_small(n);
}

std::vector<int> Multinomial::gen_small(int n) {
  tmp_keys.resize(n);
  for (int i = 0; i < n; ++ i)
    tmp_keys[i] = dist(engine) * sum_wei;
  std::sort(tmp_keys.begin(), tmp_keys.end());
  std::vector<int> ret(weight.size(), 0);
  int ptr = 0;
  int acc_w = weight[ptr];
  for (auto& k : tmp_keys) {
    while (acc_w < k) acc_w += weight[++ptr];
    ret[ptr] ++;
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
      ret *= std::pow(weight[i] / sum_wei, x[i]);
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
        x[i] * (log_weight[i] = std::log(weight[i] / sum_wei));
    }
  }
  return ret;
}

} /* namespace random */
} /* namespace swift */

