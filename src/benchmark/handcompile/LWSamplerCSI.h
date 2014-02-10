/*
 * LWSamplerCSI.h
 *
 *  Created on: Feb 10, 2014
 *      Author: yiwu
 */
#pragma once
#include <string>
#include <map>

namespace lwsampler {

class LWSamplerCSI {
public:
  LWSamplerCSI();
  ~LWSamplerCSI();
  void sample(int n); // take n samples
  void printResult();
  std::map<bool, double> getResult(); // the result is a mapping from int to probability

private:
  double total_weight; // total weight
  double* weights; // weights for each possible world
  int* ans; // answer for the query
  int loops = 1000000; // number of samples, by default 1million
  int cur_loop; // currently sampling which possible world?
  int mark_U, mark_V, mark_W, mark_X; // mark whether the corresponding varibale is sampled
  bool value_U, value_V, value_W, value_X; // store the sampled value of the variable
  bool get_U(); // get the value of U
  bool get_V(); // get the value of V
  bool get_W(); // get the value of W
  bool get_X(); // get the value of X
  void sample();
};



} /* namespace lwsampler */
