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

Multinomial::Multinomial() {
}

Multinomial::~Multinomial() {
}

void Multinomial::init(std::vector<double> wei) {
  weight = wei;
  for (size_t i = 1; i < weight.size(); ++ i)
    weight[i] += weight[i - 1];
  dist = std::uniform_real_distribution<double>(0, weight.back());
}

void Multinomial::init(double* wei, int n) {
  init(wei, wei + n);
}

void Multinomial::init(double* begin, double* end) {
  weight.clear();
  double sum = 0;
  for (double* ptr = begin; ptr != end; ++ ptr)
    weight.push_back(sum += *ptr);
  dist = std::uniform_real_distribution<double>(0, sum);
}

int Multinomial::gen() {
  return std::lower_bound(weight.begin(), weight.end(), dist(engine)) - weight.begin();
}

std::vector<int> Multinomial::gen(int n) {
  std::vector<double> key;
  for (int i = 0; i < n; ++ i)
    key.push_back(dist(engine));
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
  return std::log(likeli(x));
}

double Multinomial::likeli(const std::vector<int>& x) {
  double ret = 1;
  for (auto v : x) 
    ret *= likeli(v);
  return ret;
}
double Multinomial::loglikeli(const std::vector<int>& x) {
  return std::log(likeli(x));
}

} /* namespace random */
} /* namespace swift */
