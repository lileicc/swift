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
  n = values.size();
  weight = 1.0 / n;
  is_dist_ok = false;
  is_ind_ok = false;
  is_general = true;
  is_value_ok = true;
}

void UniformChoice::initcond(std::function<bool(int)> cf) {
  this->cond_func = cf;
  is_general = false;
}

void UniformChoice::initapp(std::function<int(int)> af) {
  this->apply_func = af;
  is_general = false;
}

void UniformChoice::init(int n) {
  this->n = n;
  is_dist_ok = false;
  is_ind_ok = false;
  is_value_ok = false;
}

int UniformChoice::gen() {
  if (is_general)
    return gen_general();
  else {
    if (cond_func)
      return gen_cond();
    else
      return gen_fast();
  }
}

int UniformChoice::gen_general() {
  if(!is_dist_ok){
    dist = std::uniform_int_distribution<int>(0, values.size() - 1);
    is_dist_ok = true;
  }
  if (values.size() == 0) return -1;
  return values[dist(engine)];
}

int UniformChoice::gen_fast() { // condition = NULL
  if (n == 0) {
    values.clear();
    is_value_ok = true;
    return -1;
  }
  if (!is_dist_ok) {
    values.clear();
    weight = 1.0 / n;
    dist = std::uniform_int_distribution<int>(0, n - 1);
    is_dist_ok = true;
  }
  int ret = dist(engine);
  if (apply_func) return apply_func(ret);
  else return ret;
}

int UniformChoice::gen_cond() { // condition = NULL
  if (n == 0) {
    values.clear();
    is_value_ok = true;
    return -1;
  }
  if (!is_dist_ok) {
    values.clear();
    for (int i = 0; i < n; ++i) {
      if (cond_func(i))
        values.push_back(i);
    }
    if (values.size() == 0) {
      is_value_ok = true;
      return -1;
    }
    weight = 1.0 / values.size();
    if (!apply_func) is_value_ok = true;
    dist = std::uniform_int_distribution<int>(0, values.size() - 1);
    is_dist_ok = true;
  }
  int ret = values[dist(engine)];
  if (apply_func) return apply_func(ret);
  else
    return ret;
}

double UniformChoice::likeli(const int& x) {
  if(!is_ind_ok) {
    if (!is_value_ok) {
      if (!is_dist_ok) { // have not sampled
        values.clear();
        if (!cond_func) {
          // must have apply_func
          for (int i=0;i<n;++i)
            values.push_back(apply_func(i));
        }
        else {
          if (apply_func) {
            for (int i=0;i<n;++i)
              if (cond_func(i))
                values.push_back(apply_func(i));
          }
          else {
            for (int i=0;i<n;++i)
              if (cond_func(i))
                values.push_back(i);
          }
        }
        weight = 1.0 / values.size();
      }
      else {
        if (cond_func) {
          for (auto&v : values)
            v = apply_func(v);
        }
        else {
          if (apply_func) {
            for (int i = 0; i < n; ++i)
              values.push_back(apply_func(i));
          }
          else {
            for (int i = 0; i<n; ++i)
              values.push_back(i);
          }
        }
      }
      is_value_ok = true;
    }
    time_stamp ++;
    if(ind.size() > SizeLimit) ind.clear();
    for(auto &v:values)
      ind[v] = time_stamp;
    is_ind_ok = true;
  }
  if (x<0) return (values.size() == 0 && is_value_ok ? 1.0 : 0);
  if(values.size() > 0 && ind[x] == time_stamp) return weight;
  return 0;
}

double UniformChoice::loglikeli(const int& x) {
  if(!is_ind_ok) {
    if (!is_value_ok) {
      if (!is_dist_ok) { // have not sampled
        values.clear();
        if (!cond_func) {
          // must have apply_func
          for (int i=0;i<n;++i)
            values.push_back(apply_func(i));
        }
        else {
          if (apply_func) {
            for (int i=0;i<n;++i)
              if (cond_func(i))
                values.push_back(apply_func(i));
          }
          else {
            for (int i=0;i<n;++i)
              if (cond_func(i))
                values.push_back(i);
          }
        }
        weight = 1.0 / values.size();
      }
      else {
        if (cond_func) {
          for (auto&v : values)
            v = apply_func(v);
        }
        else {
          if (apply_func) {
            for (int i = 0; i < n; ++i)
              values.push_back(apply_func(i));
          }
          else {
            for (int i = 0; i<n; ++i)
              values.push_back(i);
          }
        }
      }
      is_value_ok = true;
    }
    time_stamp ++;
    if(ind.size() > SizeLimit) ind.clear();
    for(auto &v:values)
      ind[v] = time_stamp;
    is_ind_ok = true;
  }
  if (x<0)return (values.size()==0&&is_value_ok?0:-INFINITY);
  if(values.size() > 0 && ind[x] == time_stamp) return log_weight;
  return -INFINITY;
}

} /* namespace random */
} /* namespace swift */
