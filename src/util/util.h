//
//  util.h
//  swift-project
//  utility functions used by the generated c++ code
//
//  Created by Lei Li on 1/18/14.
//
//

#include <cmath>
#include <vector>
#include <functional>
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
// only work for dimensionality <=
// TODO: to find a more efficient way to handle resize problem
template<typename T>
void resize(std::vector<T>& A, size_t dim, size_t sz) {
  if (dim == 0) {
    A.resize(sz);
  }
  else {
    for (auto & a : A) {
      resize(a, dim - 1, sz);
    }
  }
}

template<>
void resize<int>(std::vector<int>&A, size_t dim, size_t sz) {
  A.resize(sz);
}

//////////////////////////////////
// Internal Functions
//////////////////////////////////

/*
 * Internal function: given n, generating a vector containing 0 to n-1
 *  Note: will be used for full set operator: {type a}
 */
std::vector<int> _gen_full(int n) {
  std::vector<int> ret;
  for (int i = 0; i<n; ++i)
    ret.push_back(i);
  return ret;
}

/*
 * A filter function
 *  Input: a size <n>, and a condition function <fun>
 *  return: a vector containing all the integer k from 0 to n-1, such that fun(k) is true
 */
std::vector<int> _filter(int n, std::function<bool (int)> fun) {
  std::vector<int> ret;
  for (int i=0;i<n;++i)
    if (fun(i)) ret.push_back(i);
  return ret;
}

/*
 * filter function for range
 * Input : two iterators and a condition
 * Output: copies of filted elements in the range
 */
std::vector<int> _filter(std::vector<int>::iterator st, std::vector<int>::iterator en, std::function<bool(int)> fun) {
  std::vector<int> ret;
  for (; st != en; ++ st)
    if (fun(*st)) ret.push_back(*st);
  return ret;
}

/*
 * Count the number of filtered elements
 * Note: For the Range Version, please refer to std::count()
 */
int _count(int n, std::function<bool(int)> fun) {
  int ret=0;
  for (int i=0;i<n;++i)
    if (fun(i))++ret;
  return ret;
}

/*
 * function for forall operator in BLOG
 * Input : size <n>, and a condition function <fun>
 * Output: Whether for all the integer k from 0 to n-1, fun(k) is true
 *  Note : For range version please refer to std::all_of()
 */
bool _forall(int n, std::function<bool(int)> fun) {
  for (int i=0;i<n;++i)
    if (!fun(i)) return false;
  return true;
}

/*
* function for exists operator in BLOG
* Input : size <n>, and a condition function <fun>
* Output: Whether there exists a integer k from 0 to n-1, such that fun(k) is true
*  Note : For range version please refer to std::any_of()
*/
bool _exists(int n, std::function<bool(int)> fun) {
  for (int i=0;i<n;++i)
    if (fun(i)) return true;
  return false;
}
