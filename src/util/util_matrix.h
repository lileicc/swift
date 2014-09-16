//
//  util_matrix.h
//  swift-project
//  utility functions for matrix used by the generated c++ code
//
//  Matrix computation supported by "armadillo"
//
//  Created by Yi Wu on 9/15/14.
//

#pragma once

#include <cstring>
#include <cmath>
#include <vector>
#include <functional>
#include <iostream>

#include "armadillo"

using namespace arma;
using namespace std;

// convert a vector containing all the elements to a row x col matrix
inline mat _to_matrix(const vector<double>& val, int row, int col) {
  return mat(val.data(), row, col);
}

// convert a vector<vector> to a real matrix
inline mat _to_matrix(const vector<vector<double>>& val) {
  int row = val.size();
  if (row == 0)return mat();
  int col = val[0].size();
  for (size_t i = 0; i < val.size(); ++ i)
    if (val[i].size() > col) col = val[i].size();
  mat ret(row, col);
  for (int i = 0; i < row; ++ i)
    for (int j = 0; j < col; ++ j)
      ret(i, j) = val[i][j];
  return ret;
}
