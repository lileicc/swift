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

UniformChoice::UniformChoice()
  : is_dist_ok(false), is_ind_ok(false) {
  time_stamp = 0;
}

UniformChoice::~UniformChoice() {
}

void UniformChoice::init(std::vector<int> values) {
  this->values = values;
  weight = 1.0 / values.size();
  is_dist_ok = false;
  is_ind_ok = false;
}

template<typename _RD>
int UniformChoice::gen(_RD& rd) {
  return values[dist(rd)];
}

int UniformChoice::gen() {
  if(!is_dist_ok){
    dist = std::uniform_int_distribution<int>(0, values.size() - 1);
    is_dist_ok = true;
  }
  return gen(engine);
}

double UniformChoice::likeli(const int& x) {
  if(!is_ind_ok) {
    time_stamp ++;
    if(ind.size() > SizeLimit) ind.clear();
    for(auto &v:values)
      ind[v] = time_stamp;
    is_ind_ok = true;
  }
  if(ind[x] == time_stamp) return weight;
  return 0;
}

double UniformChoice::loglikeli(const int& x) {
  if(!is_ind_ok) {
    if (ind.size() > SizeLimit) {
      ind.clear();
      time_stamp = 0;
    }
    time_stamp++;
    for(auto &v:values)
      ind[v] = time_stamp;
    log_weight = - std::log(values.size());
    is_ind_ok = true;
  }
  if(ind[x] == time_stamp) return log_weight;
  return -INFINITY;
}

} /* namespace random */
} /* namespace swift */
