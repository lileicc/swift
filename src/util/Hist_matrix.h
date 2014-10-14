/*
 * Hist_matrix.h
 *   Special hist for matrix
 * 
 *  Created on: Sept 17, 2014
 *      Author: yiwu
 */
#pragma once

#include "Hist.h"

#include "armadillo"

using namespace arma;

/**
 * special histogram for matrix
 */

namespace swift {

template<>
class Hist<mat> {
private:
  std::vector<std::pair<mat, double> > table;
  const bool isLogarithm;
  mat sum;
  double sum_wei;
  bool init_flag;
public:
  void clear() {
    init_flag = false;
    table.clear();
  }

  Hist(bool isLogarithm = true) :
    isLogarithm(isLogarithm) {
    clear();
  }
  ;
  virtual ~Hist() {
  }
  ;

  void add(mat element, double weight) {
    mat cur;
    if (init_flag) {
      sum += cur;
      if (isLogarithm) {
        sum_wei = logsum(sum_wei, weight);
      } else {
        sum_wei += weight;
      }
    } else {
      init_flag = true;
      sum = cur;
      sum_wei = weight;
    }
    if (isLogarithm) {
      cur = element * std::exp(weight);
    }
    else {
      cur = element * weight;
    }

    table.push_back(std::make_pair(element, weight));
  }
  ;

  std::vector<std::pair<mat, double>> & getResult() {
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

  std::vector<std::pair<mat, double>> getNormalizedResult() {
    std::vector<std::pair<mat, double> >normtab;
    double w = getTotalWeight();
    for (auto & it : table) {
      if (isLogarithm)
        it.second = std::exp(it.second - w);
      else
        it.second = it.second / w;
    }
    return normtab;
  }
  ;

  void print(std::string str = std::string()) {
    if(str.size() > 0)
      printf(">> query : %s\n", str.c_str());
    if (isLogarithm) sum_wei = std::exp(sum_wei);
    mat mean = sum / sum_wei;
    mat cov = mean, var = mean;
    cov.zeros(); var.zeros();
    for (auto& it : table) {
      cov += (isLogarithm ? exp(it.second) : it.second) * ((it.first - mean) * trans(it.first - mean));
      var += (isLogarithm ? exp(it.second) : it.second) * ((it.first - mean) % (it.first - mean));
    }
    cov /= sum_wei;
    var /= sum_wei;
#ifndef NO_PRINT
    mean.print("Mean : ");
    var.print( "Var  : ");
    cov.print( "Cov  : ");
#endif
    clear();
  }

  void debug() {
    for (auto& it : getResult()) {
      it.first.print(cerr, "weight = " + toString(isLogarithm ? exp(it.second) : it.second) + " :");
    }
  }
};
}
