/*
 * Hist.h
 *
 *  Created on: Jan 12, 2014
 *      Author: leili
 */
#pragma once

#include <map>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#include "util.h"

namespace swift {
/**
 * histogram for storing answer
 */
template<class T>
class Hist {
private:
  std::map<T, double> table;
  const bool isLogarithm;
public:
  Hist(bool isLogarithm = true) :
      isLogarithm(isLogarithm) {
  }
  ;
  virtual ~Hist() {
  }
  ;

  void add(T element, double weight) {
    if (table.find(element) != table.end()) {
      if (isLogarithm) {
        if (weight > -INFINITY)
          table[element] = logsum(weight, table[element]);
      } else {
        if (weight > 0)
          table[element] += weight;
      }
    } else {
      if (isLogarithm) {
        if (weight > -INFINITY)
          table[element] = weight;
      } else {
        if (weight > 0)
          table[element] = weight;
      }
    }
  }
  ;

  std::map<T, double> & getResult() {
    return table;
  }
  ;

  double getTotalWeight() {
    double w = 0;
    auto it = table.begin();
    if (it == table.end()) {
      return 0;
    }
    w = it->second;
    it++;
    for (; it != table.end(); it++) {
      if (isLogarithm) {
        w = logsum(w, it->second);
      } else {
        w += it->second;
      }
    }
    return w;
  }

  std::map<T, double> getNormalizedResult() {
    std::map<T, double> normmap;
    double w = getTotalWeight();
    for (auto & it : table) {
      if (isLogarithm)
        normmap[it.first] = std::exp(it.second - w);
      else
        normmap[it.first] = it.second / w;
    }
    return normmap;
  }
  ;

  void print() {
    for (auto& it : getNormalizedResult()) {
      printf("%s -> %s\n", std::to_string(it.first).c_str(),
          std::to_string(it.second).c_str());
    }
  }

  void debug() {
    for (auto& it : getResult()) {
      fprintf(stderr, "%s -> %s\n", std::to_string(it.first).c_str(),
          std::to_string(isLogarithm ? std::exp(it.second) : it.second).c_str());
    }
  }
};

// Special Hist for Real
template<>
class Hist<double> {
private:
  const int MAX_ELEMENT_NUM = 10000;

  std::vector<std::pair<double, double> > table;
  const bool isLogarithm;
  std::vector<double> bucket;
  double sum, sum_sqr, sum_wei;
  double lo, hi, det;
  double left_bound, right_bound;
  bool bucketFixed;
  int n;

  inline void add_to_bucket(double p, double w) {
    int k;
    if (p <= lo) {
      k = 0;
      left_bound = std::min(left_bound, p);
    }
    else
    if (p >= hi) {
      k = n - 1;
      right_bound = std::max(right_bound, p);
    }
    else {
      k = (int)std::floor((p - lo) / det);
    }
    if (isLogarithm) bucket[k] = logsum(bucket[k], w);
    else bucket[k] += w;
  }

  void build_bucket() {
    lo = std::floor(lo);
    hi = std::ceil(hi);
    left_bound = lo;
    right_bound = hi;
    det = (hi - lo) / n;
    bucketFixed = true;
    for (auto& p : table)
      add_to_bucket(p.first, p.second);
  }

  inline void add_normal(double p, double w) {
    table.push_back(std::make_pair(p, w));
    if (p < lo) lo = p;
    if (p > hi) hi = p;
    if (table.size() == MAX_ELEMENT_NUM)
      build_bucket();
  }
public:
  Hist(bool isLogarithm = true, int bucket_n = 10) :
    isLogarithm(isLogarithm) {
    sum = sum_wei = 0;
    bucket.resize(bucket_n);
    n = bucket_n;
    lo = 1e100;
    hi = -1e100;
    bucketFixed = false;
  }
  ;
  virtual ~Hist() {
  }
  ;

  void setBucket(int bucket_n, double _lo, double _hi) {
    bucket.resize(n = bucket_n);
    left_bound = lo = _lo;
    right_bound = hi = _hi;
    det = (hi - lo) / n;
    bucketFixed = true;
  }

  void setBucket(int bucket_n) {
    bucket.resize(n = bucket_n);
    lo = 1e100;
    hi = -1e100;
    bucketFixed = false;
  }

  void add(double element, double weight) {
    if (isLogarithm) {
      sum += element * std::exp(weight);
      sum_sqr += element * element * std::exp(weight);
      sum_wei = logsum(sum_wei, weight);
    }
    else {
      sum += element * weight;
      sum_sqr += element * element * weight;
      sum_wei += weight;
    }
    if (bucketFixed)
      add_to_bucket(element, weight);
    else
      add_normal(element, weight);
  }
  ;

  std::vector<std::pair<double, double> > & getResult() {
    return table;
  }
  ;

  double getTotalWeight() {
    return sum_wei;
  }

  void print() {
    if (isLogarithm) sum_wei = std::exp(sum_wei);
    double mean = sum / sum_wei;
    double mean_sqr = sum_sqr / sum_wei;
    double var = mean * mean - mean_sqr;
    printf("Mean = %.5lf   Var = %.5lf\n", mean, var);
    if (!bucketFixed)
      build_bucket();
    double cur = lo;
    for (int i = 0; i < n; ++i) {
      if (isLogarithm)
        bucket[i] = std::exp(bucket[i] - sum_wei);
      else
        bucket[i] /= sum_wei;
      printf("%c%lf, %lf] -> %.5lf\n", (i == 0 ? '[' : '('), (i == 0 ? left_bound : cur), (i == n - 1 ? right_bound : cur + det), bucket[i]);
      cur += det;
    }
  }

  void debug() {
    std::sort(table.begin(), table.end());
    for (auto& it : table) {
      fprintf(stderr, "%s -> %s\n", std::to_string(it.first).c_str(),
        std::to_string(isLogarithm ? std::exp(it.second) : it.second).c_str());
    }
  }
};
}
