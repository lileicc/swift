//
//  util.h
//  swift-project
//  utility functions used iby the generated c++ code
//
//  Created by Lei Li on 1/18/14.
//
//

#include <cmath>
#pragma once


// computing log( exp(a) + exp(b) )
// NOTE this function cannot handle infinity
template <typename T>
T logsum(T a, T b) {
  if (a == b) {
    return a + log(2);
  } else if (a > b) {
    return a + log(1 + exp(b - a));
  } else {
    return b + log(1 + exp(a - b));
  }
}

// calculating log(a == b)
template <typename T>
double logEqual(T a, T b) {
  return (a == b) ? 0 : - INFINITY;
}