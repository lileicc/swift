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

// resize the vector or vector of vector
// Args:
//   id, indicating the dimension which needs resizing, (starting from 0)
//   sz, the size resizing to 
// only work for dimensionality <= 3
template<typename T>
inline void resize(std::vector<T> & x, size_t id, size_t sz){
  if (id == 0) {
    // resize the first dimension
    if (x.size() > 0)
      x.resize(sz, x[0]);
    else
      x.resize(sz);
  } else if (id == 1) {
    if (x.size() > 0 && x[0].size() > 0) {
      // resize the second dimension
      for (auto & a : x) {
        a.resize(sz, x[0][0]);
      }
    } else {
      for (auto & a : x) {
        a.resize(sz);
      }
    }
  } else if (id == 2) {
    for (auto & a : x) {
      for (auto & b : a) {
        b.resize(sz);
      }
    }
  }
}

template<typename _T>
inline void append(std::vector<_T> & x, size_t n, const _T & value) {
  x.insert(x.end(), n, value);
}