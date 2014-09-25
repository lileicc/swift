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

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <cstdarg>

#include "armadillo"

using namespace arma;

namespace swift {

#define _predecl_colsum(a) (arma::sum(a,0))
#define _predecl_rowsum(a) (arma::sum(a,1))

// get submatrix from a large matrix
inline mat _mat_getrow(const mat& m, int r) {
  return m.row(r);
}
inline mat _mat_getcol(const mat& m, int c) {
  return m.col(c);
}
inline mat _mat_getrows(const mat&m, int r1, int r2) {
  return m.rows(r1, r2);
}
inline mat _mat_getcols(const mat&m, int c1, int c2) {
  return m.cols(c1, c2);
}
inline mat _mat_submat(const mat&m, int r1, int c1, int r2, int c2) {
  return m.submat(r1,c1,r2,c2);
}

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


mat loadRealMatrix(std::string filename, int x1 = -1, int x2 = -1, int y1 = -1, int y2 = -1) {
  static std::unordered_map<std::string, std::shared_ptr<mat> > matStore;
  std::shared_ptr<mat> ret;
  if (matStore.count(filename) > 0) {
    ret = matStore[filename];
  }
  else {
    ret = std::make_shared<mat>();
    if (!ret->load(filename.c_str())) {
      std::cerr << "[ Run-Time Error ] >> Matrix Loading Failure on < " + filename + " >!"<<std::endl;
      std::exit(0);
    }
    matStore[filename] = ret;
  }
  if (x1 < 0)
    return *(ret.get());
  if (x2 < 0)
    return ret->row(x1);
  if (y1 < 0 || y2 < 0)
    return ret->rows(x1, x2);
  return ret->submat(x1, y1, x2, y2);
}
}
