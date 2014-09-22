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
  Hist(bool isLogarithm = true) :
    isLogarithm(isLogarithm) {
    sum_wei = 0;
    init_flag = false;
  }
  ;
  virtual ~Hist() {
  }
  ;

  void add(mat element, double weight) {
    mat cur;
    if (isLogarithm) {
      cur = element * exp(weight);
      sum_wei = logsum(sum_wei, weight);
    }
    else {
      cur = element * weight;
      sum_wei += weight;
    }
    if (init_flag) sum += cur;
    else {
      init_flag = true;
      sum = cur;
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
        it.second = exp(it.second - w);
      else
        it.second = it.second / w;
    }
    return normtab;
  }
  ;

  void print() {
    if (isLogarithm) sum_wei = exp(sum_wei);
    mat mean = sum / sum_wei;
    mat var = 0;
    for (auto& it : table)
      var += (isLogarithm ? exp(it.second) : it.second) * ((it.first - mean) * trans(it.first - mean));
    var /= sum_wei;
    mean.print("Mean : ");
    var.print("Variance : ");
  }

  void debug() {
    for (auto& it : getResult()) {
      it.first.print(cerr, "weight = " + std::to_string(isLogarithm ? exp(it.second) : it.second) + " :");
    }
  }
};
}
