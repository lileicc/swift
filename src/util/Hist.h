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
  std::map<double, double> table;
  const bool isLogarithm;
  std::vector<double> bucket;
  double sum, sum_wei;
public:
  Hist(bool isLogarithm = true, int bucket_n = 10) :
    isLogarithm(isLogarithm) {
    sum = sum_wei = 0;
    bucket.resize(bucket_n);
  }
  ;
  virtual ~Hist() {
  }
  ;

  void setBucket(int bucket_n) {
    bucket.resize(bucket_n);
  }

  void add(double element, double weight) {
    if (isLogarithm) {
      sum += element * std::exp(weight);
      sum_wei = logsum(sum_wei, weight);
    }
    else {
      sum += element * weight;
      sum_wei += weight;
    }

    if (table.find(element) != table.end()) {
      if (isLogarithm) {
        if (weight > -INFINITY)
          table[element] = logsum(weight, table[element]);
      }
      else {
        if (weight > 0)
          table[element] += weight;
      }
    }
    else {
      if (isLogarithm) {
        if (weight > -INFINITY)
          table[element] = weight;
      }
      else {
        if (weight > 0)
          table[element] = weight;
      }
    }
  }
  ;

  std::map<double, double> & getResult() {
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
      }
      else {
        w += it->second;
      }
    }
    return w;
  }

  std::map<double, double> getNormalizedResult() {
    std::map<double, double> normmap;
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
    if (isLogarithm) sum_wei = std::exp(sum_wei);
    double mean = sum / sum_wei;
    double var = 0;
    for (auto& it : table)
      var += (isLogarithm ? std::exp(it.second) : it.second) * (it.first - mean) * (it.first - mean);
    var /= sum_wei;
    printf("Mean = %.5lf   Var = %.5lf\n", mean, var);
    std::fill(bucket.begin(), bucket.end(), 0);
    double lo = std::floor(table.begin()->first);
    double hi = std::ceil(table.rbegin()->first);
    int n = bucket.size();
    double det = (hi - lo) / n, cur = lo;
    int pt = 0;
    for (auto& it : getNormalizedResult()) {
      while (it.first - cur > det && pt < n - 1) {
        ++pt; cur += det;
      }
      if (isLogarithm) bucket[pt] = logsum(bucket[pt], it.second);
      else bucket[pt] += it.second;
    }
    cur = lo;
    for (int i = 0; i < n; ++i) {
      printf("%c%.lf, %lf] -> %.5lf\n", (i == 0 ? '[' : '('), cur, cur + det, bucket[i]);
      cur += det;
    }
  }

  void debug() {
    for (auto& it : getResult()) {
      fprintf(stderr, "%.5lf -> %.5lf\n", it.first,
        isLogarithm ? std::exp(it.second) : it.second);
    }
  }
};
