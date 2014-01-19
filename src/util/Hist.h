/*
 * Hist.h
 *
 *  Created on: Jan 12, 2014
 *      Author: leili
 */
#include <map>
#include <cstdio>
#include "util.h"
#pragma once

/**
 * histogram for storing answer
 */
template <class T>
class Hist {
private:
  std::map<T, double> table;
  const bool isLogarithm;
public:
  Hist(bool isLogarithm=true) : isLogarithm(isLogarithm) {};
  virtual ~Hist() {};
  
  void add(T element, double weight) {
    if (table.find(element) != table.end()) {
      if (isLogarithm)
        weight = logsum(weight, table[element]);
      else
        weight += table[element];
    }
    table[element] = weight;
  };

  std::map<T, double> & getResult(){
    return table;
  };
  
  double getTotalWeight() {
    double w = 0;
    auto it = table.begin();
    if (it == table.end()) {
      return 0;
    }
    w = it->second;
    it ++;
    for (; it != table.end(); it ++) {
      if (isLogarithm) {
        w = logsum(w, it->second);
      } else {
        w += it->second;
      }
    }
    return w;
  }
  
  std::map<T, double> getNormalizedResult(){
    std::map<T, double> normmap;
    double w = getTotalWeight();
    for (auto & it : table) {
      if (isLogarithm)
        normmap[it.first] = exp(it.second - w);
      else
        normmap[it.first] = it.second / w;
    }
    return normmap;
  };
  
  void print() {
    for (auto& it : getNormalizedResult()) {
      printf("%s -> %s\n", std::to_string(it.first).c_str(), std::to_string(it.second).c_str());
    }
  }
};


