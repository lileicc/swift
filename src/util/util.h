//
//  util.h
//  swift-project
//  utility functions used iby the generated c++ code
//
//  Created by Lei Li on 1/18/14.
//
//

#pragma once

#include <cstring>
#include <cmath>
#include <vector>
#include <functional>
#include "../random/Multinomial.h"

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

/**
 *  append n repeated values to the tail of the vector
 *
 *  @param x     vector
 *  @param n     number of elements to append
 *  @param value the value to add
 */
template<typename _T>
inline void append(std::vector<_T> & x, size_t n, const _T & value) {
  x.insert(x.end(), n, value);
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

/*
 * Resample Function
 * For Particle Filtering
 *   Using Multinomial Distribution
 * >> Input Arguments:
 *    > template: Dependency, SampleN, class name for static memorization, class name for temporal memorization
 *    > arguments: weight, {static memorization and ptr}, {temporal memorization, ptr and backup ptr}
 */
template<int Dependency, int SampleN, class stat_T, class temp_T>
void resample(
  double* weight, 
  stat_T stat_memo[SampleN], stat_T* ptr_stat_memo[SampleN], 
  temp_T temp_memo[Dependency][SampleN], temp_T* ptr_temp_memo[Dependency][SampleN], temp_T* backup_ptr[Dependency][SampleN]) {
  swift::random::Multinomial dist;
  dist.init(weight, weight + SampleN);
  std::vector<int> candidate = dist.gen(SampleN);
  for(int i = 0; i < SampleN; ++ i) {
    int pos = candidate[i];
    // Swap Static States
    ptr_stat_memo[i] = stat_memo + pos;
    for(int j = 0; j < Dependency; ++ j)
      backup_ptr[j][i] = ptr_temp_memo[j][pos];
  }
  
  std::memcpy(ptr_temp_memo, backup_ptr, sizeof(temp_T*) * Dependency * SampleN);
}

/*
 * Pointer Copy function
 * For Particle Filtering
 * >> Input Arguments:
 *    > ptr: array containing pointers
 *    > state: array that ptr points to
 * >> Usage:
 *    > make sure ptr[i] points to state[i]
 */
template<class State>
void pointer_copy(State** ptr, State* state, int N) {
  for(int i=0;i<N;++i)
    ptr[i] = state + i;
}

// Internal Function for TimeStep Operation
inline unsigned prev(unsigned u) {return u - 1;}
inline unsigned prev(unsigned u, int t) {return u - t;}
