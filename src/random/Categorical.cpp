/*
 * Categorical.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */
#include <numeric>
#include <cmath>
#include "Categorical.h"

namespace swift {
namespace random {

Categorical::Categorical() {
}

Categorical::~Categorical() {
}

void Categorical::init(const std::map<int, double>& ws) {
  values.clear();
  weights.clear();
  values_to_indic.clear();
  log_weights.clear();
  int i = 0;
  for (auto it : ws) {
    if (it.second > 0 && it.second <= 1) {
      values.push_back(it.first);
      weights.push_back(it.second);
      values_to_indic[it.first] = i;
      log_weights.push_back(std::log(it.second));
      i++;
    }
  }
  /*
   Note: In VS2013, we have to rewrite the last line with the following code
   
  auto lis = std::initializer_list<double>(weights.data(), weights.data() + weights.size());
  dist = std::discrete_distribution<int>(lis);
   */
  dist = std::discrete_distribution<int>(weights.begin(), weights.end());
}

void Categorical::init(std::vector<int> val, std::vector<double> wei) {
  values.clear();
  weights.clear();
  values_to_indic.clear();
  log_weights.clear();
  for (size_t i = 0; i < val.size() && i < wei.size(); ++ i) {
    values.push_back(val[i]);
    weights.push_back(wei[i]);
    values_to_indic[val[i]] = i;
    log_weights.push_back(std::log(wei[i]));
  }
  /*
  Note: In VS2013, we have to rewrite the last line with the following code
  
  auto lis = std::initializer_list<double>(weights.data(), weights.data() + weights.size());
  dist = std::discrete_distribution<int>(lis);
   */
  dist = std::discrete_distribution<int>(weights.begin(), weights.end());
}

template<typename _RD>
int Categorical::gen(_RD& rd) {
  return values[dist(rd)];
}

int Categorical::gen() {
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

double Categorical::likeli(const int& x) {
  auto e = values_to_indic.find(x);
  if (e != values_to_indic.end())
    return weights[e->second];
  else
    return 0;
}

double Categorical::loglikeli(const int& x) {
  // todo: check -infinity!!!
  auto e = values_to_indic.find(x);
  if (e != values_to_indic.end())
    return log_weights[e->second];
  else
    return - INFINITY;
}

} /* namespace random */
} /* namespace swift */
