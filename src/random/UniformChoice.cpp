/*
 * UniformChoice.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */
#include <numeric>
#include <cmath>
#include "UniformChoice.h"

namespace swift {
namespace random {

UniformChoice::UniformChoice() {
  time_stamp = 0;
}

UniformChoice::~UniformChoice() {
}

void UniformChoice::init(std::vector<int> values) {
  this->values = values;
  weight = 1.0 / values.size();
  log_weight = - std::log(values.size());
  time_stamp ++;
  if(ind.size() > SizeLimit) ind.clear();
  for(auto &v:values)
    ind[v] = time_stamp;
  dist = std::uniform_int_distribution<int>(0, values.size() - 1);
}

template<typename _RD>
int UniformChoice::gen(_RD& rd) {
  return values[dist(rd)];
}

int UniformChoice::gen() {
  return gen(engine);
}

double UniformChoice::likeli(const int& x) {
  if(ind[x] == time_stamp) return weight;
  return 0;
}

double UniformChoice::loglikeli(const int& x) {
  if(ind[x] == time_stamp) return log_weight;
  return -INFINITY;
}

} /* namespace random */
} /* namespace swift */
