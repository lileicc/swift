//
//  util.h
//  swift-project
//  utility functions used iby the generated c++ code
//
//  Created by Lei Li on 1/18/14.
//
//

#include <cmath>
#include <vector>
#pragma once

// computing log( exp(a) + exp(b) )
// NOTE this function cannot handle infinity
template<typename T>
inline T logsum(T a, T b) {
  if (a == b) {
    return a + log(2);
  } else if (a > b) {
    return a + log(1 + exp(b - a));
  } else {
    return b + log(1 + exp(a - b));
  }
}

// calculating log(a == b)
template<typename T>
inline double logEqual(T a, T b) {
  return (a == b) ? 0 : - INFINITY;
}

// resize the vector of int
template<typename T>
inline void resize(std::vector<T> & x, int id, int sz){
  x.resize(sz);
}

// resize the matrix (vector of vector of int)
template<typename T>
inline void resize(std::vector<std::vector<T> >& x, int id, int sz){
  if (id == 0) {
    // resize the first dimension
    int b = 1;
    if (x.size() > 0)
      b = x[0].size();
    x.resize(sz, std::vector<T>(b));
  } else if (id == 1) {
    // resize the second dimension
    for (auto & a : x) {
      a.resize(sz);
    }
  } else {
    // do nothing
  }
}