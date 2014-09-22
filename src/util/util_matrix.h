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

namespace swift {

// convert a vector containing all the elements to a row x col matrix
inline mat _to_matrix(const std::vector<double>& val, int row, int col) {
  return mat(val.data(), row, col);
}

// convert a vector<vector> to a real matrix
inline mat _to_matrix(const std::vector<std::vector<double>>& val) {
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


// horizontally stack all the matrix/col vector
mat hstack(int n_param, ...) {
  va_list args;
  va_start(args, n_param);
  mat ret;
  for (int i = 0; i < n_param; ++i) {
    if (i == 0) ret = va_arg(args, mat);
    else ret = join_horiz(ret, va_arg(args, mat));
  }
  va_end(args);
  return ret;
}

// vertically stack all the matrix/row vector
mat vstack(int n_param, ...) {
  va_list args;
  va_start(args, n_param);
  mat ret;
  for (int i = 0; i < n_param; ++i) {
    if (i == 0) ret = va_arg(args, mat);
    else ret = join_vert(ret, va_arg(args, mat));
  }
  va_end(args);
  return ret;
}
}
