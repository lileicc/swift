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
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <random>
#include <array>

namespace swift {

// Type Conversion Functions
//  convert to Int
template<class T>
inline int toInt(const T& a) {return (int) a;}
template<>
inline int toInt<std::string>(const std::string& a) {
  int ret = 0;
  std::sscanf(a.c_str(), "%d", &ret);
  return ret;
}
//   convert to Double
template<class T>
inline double toReal(const T& a) { return (double)a; }
template<>
inline double toReal<std::string>(const std::string& a) {
  double ret = 0;
  std::sscanf(a.c_str(), "%lf", &ret);
  return ret;
}

// convert to String
template<class T>
inline std::string toString(const T& a) { return std::to_string(a); }
template<>
inline std::string toString<std::string>(const std::string& a) { return a; }
template<>
inline std::string toString<bool>(const bool&a) {return a ? "true" : "false";}
// @ISSUE: Currently we do not support char and treat boolean as char
template<>
inline std::string toString<char>(const char&a) { return a ? "true" : "false"; }
template<>
inline std::string toString(const std::vector<int>& v) {
  std::string ret = "[";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i) ret.push_back(',');
    ret.append(std::to_string(v[i]));
  }
  ret.push_back(']');
  return ret;
}

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
* Allowed Aggregator functions for set aggregation
*  Input: referenced aggregator and value to aggregate
*/
template<class T>
void _aggr_sum(T&aggr, const T&k) {
  aggr+=k;
}

template<class T>
void _aggr_min(T&aggr, const T&k) {
  if (k < aggr) aggr = k;
}

template<class T>
void _aggr_max(T&aggr, const T&k) {
  if (k > aggr) aggr = k;
}

/*
* General Aggregation Function for a set/array
* Input: a set and an aggregation function (and applied function for a TupeSet)
*/
template<class T>
T _aggregate(const std::vector<T>& st, std::function<void(T&, const T&)> aggr) {
  if (st.size() == 0) return T();
  auto it = st.begin();
  T ret = *it ++;
  for (; it != st.end(); it++)
    aggr(ret, *it);
  return ret;
}

template<class T>
T _aggregate(int n, std::function<T(int)> fun, std::function<void(T&, const T&)> aggr) {
  if (n == 0) return T();
  T ret = fun(0);
  for (int i = 1; i < n; ++ i)
    aggr(ret, fun(i));
  return ret;
}

template<class T>
T _aggregate(int n, std::function<bool(int)> cond, std::function<T(int)> fun, std::function<void(T&, const T&)> aggr) {
  if (n == 0) return T();
  bool flag = false;
  T ret=T();
  for (int i = 0; i < n; ++i) {
    if (cond(i)) {
      if (flag)
        aggr(ret,fun(i));
      else {
        ret = fun(i);
        flag=true;
      }
    }
  }
  return ret;
}

/*
 * A filter function
 *  Input: a size <n>, and a condition function <fun>
 *  return: a vector containing all the integer k from 0 to n-1, such that fun(k) is true
 */
std::vector<int> _filter(int n, std::function<bool (int)> fun) {
  std::vector<int> ret;
  ret.reserve(n);
  for (int i=0;i<n;++i)
    if (fun(i)) ret.push_back(i);
  return ret;
}

/*
 * filter function for set
 * Input : set/array and a condition
 * Output: copies of filted elements in the range
 */
std::vector<int> _filter(const std::vector<int>&st, std::function<bool(int)> cond) {
  std::vector<int> ret;
  ret.reserve(st.size());
  for (auto& u : st)
    if (cond(u)) ret.push_back(u);
  return ret;
}

/*
* filter function for range
* Input : begin and end iterators of a range and a condition
* Output: copies of filted elements in the range
*/
std::vector<int> _filter(std::vector<int>::iterator st, std::vector<int>::iterator en, std::function<bool(int)> cond) {
  std::vector<int> ret;
  for (; st != en; ++ st)
    if(cond(*st)) ret.push_back(*st);
  return ret;
}

/*
 * apply function for list of elements
 * Input : a list of input elements and a function to apply
 * Output : an *unsorted* list (namely an unordered_set) of output of the function
 */
template<class ret_T, class in_T>
std::vector<ret_T> _apply(std::vector<in_T> args, std::function<ret_T(in_T)> fun) {
  std::vector<ret_T>ret;
  ret.reserve(args.size());
  for(auto &u : args)
    ret.push_back(fun(u));
  return ret;
}

template<class ret_T>
std::vector<ret_T> _apply(int n, std::function<ret_T(int)> fun) {
  std::vector<ret_T>ret(n);
  for (int i = 0; i < n; ++ i)
    ret[i] = fun(i);
  return ret;
}

template<class ret_T>
std::vector<ret_T> _apply(int n, std::function<bool(int)> cond, std::function<ret_T(int)> fun) {
  std::vector<ret_T>ret;
  ret.reserve(n);
  for (int i = 0; i < n; ++i)
    if (cond(i))
      ret.push_back(fun(i));
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
 * Normalize Log-Weights
 *  For Particle Filtering
 */
template<int SampleN>
void normalizeLogWeights(double *weight) {
  double maxval = *std::max_element(weight, weight + SampleN);
  double* endptr = weight + SampleN;
  for (; weight != endptr; ++weight) {
    *weight = std::exp(*weight - maxval);
  }
}

/*
 * Resample Function
 *  For Particle Filtering
 * >> Input Arguments:
 *    > template: SampleN, Dependency, class name for static memorization, class name for temporal memorization
 *    > arguments: weight, {static memorization and ptr}, {temporal ptr and backup ptr}
 */
template<int SampleN, int Dependency, class stat_T, class temp_T>
void resample(
  double* weight,
  stat_T stat_memo[SampleN], stat_T ptr_stat_memo[SampleN],
  temp_T* ptr_temp_memo[SampleN][Dependency], temp_T* backup_ptr[SampleN][Dependency]) {
  static std::uniform_real_distribution<double> dist(0, 1);
  static std::default_random_engine gen;

  for (int i = 1; i<SampleN; ++i) {
    weight[i] += weight[i - 1];
  }
  double sum_wei = weight[SampleN - 1];
  double ratio = sum_wei / SampleN;
  double basis = 0;
  double tar = 0;

  int pos = 0;
  for (int i = 0; i < SampleN; ++i) {
    tar = basis + dist(gen) * ratio;
    basis += ratio;
    for (; weight[pos]<tar; ++pos);
    ptr_stat_memo[i] = stat_memo[pos];
    memcpy(backup_ptr[i], ptr_temp_memo[pos], sizeof(temp_T*)* Dependency);
  }
  std::memcpy(ptr_temp_memo, backup_ptr, sizeof(temp_T*)* Dependency * SampleN);
  std::memcpy(stat_memo, ptr_stat_memo, sizeof(stat_T)* SampleN);
}

/*
 * Pointer Copy function
 * For Particle Filtering
 * >> Input Arguments:
 *    > t: current time step
 *    > ptr: pointers
 *    > state: memorization data structure
 * >> Usage:
 *    > make sure ptr[i][t] points to state[i][t]
 */
template<int SampleN, int Dependency, class State>
void pointer_copy(int t, State* ptr[SampleN][Dependency], State state[SampleN][Dependency]) {
  for (int i = 0; i<SampleN; ++i)
    ptr[i][t] = state[i] + t;
}

// Internal Function for TimeStep Operation
inline unsigned prev(unsigned u) {return u - 1;}
inline unsigned prev(unsigned u, int t) {return u - t;}

inline double randn() {
  static std::default_random_engine generator;
  static std::normal_distribution<double> stdnorm(0, 1);
  return stdnorm(generator);
}


///////// Utils for Perturbation in Liu-West Filter /////////
// Perturbation for Double variable #func#
#define rho (0.97)

#define __perturb(func) {\
  double mean, stddev, new_val, old_val; \
  mean = 0; stddev = 0; \
  for (int i = 0; i < _ParticleN_; ++i)\
    mean += _stat_memo[i].__value_##func; \
  mean /= _ParticleN_; \
  for (int i = 0; i<_ParticleN_; ++i) {\
    double det = _stat_memo[i].__value_##func - mean; \
    stddev += det * det; \
  }\
  stddev = sqrt(stddev / _ParticleN_); \
  for (int i = 0; i < _ParticleN_; ++i) {\
    old_val = _stat_memo[i].__value_##func; \
    new_val = rho * old_val + (1 - rho) * mean + \
    sqrt(1 - rho * rho) * stddev * randn(); \
    _stat_memo[i].__value_##func = new_val; \
  }\
}
// Perturbation for matrix variable #func#
#define __perturb_matrix(func) {\
  int _n_rows = _stat_memo[0].__value_##func.n_rows; \
  int _n_cols = _stat_memo[0].__value_##func.n_cols; \
  mat mean, stddev, new_val, old_val; \
  mean = zeros(_n_rows, _n_cols); stddev = zeros(_n_rows, _n_cols); \
  for (int i = 0; i<_ParticleN_; ++i)\
    mean += _stat_memo[i].__value_##func; \
  mean /= (double)_ParticleN_; \
  for (int i = 0; i<_ParticleN_; ++i)\
    stddev += (_stat_memo[i].__value_##func - mean) % \
      (_stat_memo[i].__value_##func - mean); \
  stddev /= (double) _ParticleN_;\
  stddev = sqrt(stddev); \
  for (int i = 0; i<_ParticleN_; ++i) { \
    old_val = _stat_memo[i].__value_##func; \
    new_val = rho * old_val + (1 - rho) * mean + \
    sqrt(1 - rho * rho) * (stddev % arma::randn(_n_rows, _n_cols)); \
    _stat_memo[i].__value_##func = new_val; \
  }\
}
// Perturbation for MultiDimensional Random Function
//    --> currently only support at most 2D random var
#define __perturb_dim1(func) {\
  int _n = _stat_memo[0].__value_##func .data.size(); \
  for (int _i = 0; _i < _n; ++_i) {\
    __perturb(##func [_i]); \
  }\
}
#define __perturb_dim2(func) {\
  int _n = _stat_memo[0].__value_##func.data.size(); \
  int _m = _stat_memo[0].__value_##func .data[0].size(); \
  for (int _i = 0; _i < _n; ++_i) {\
    for (int _j = 0; _j < _m; ++_j) {\
      __perturb(##func [_i][_j]); \
    }\
  }\
}
#define __perturb_matrix_dim1(func) {\
  int _n = _stat_memo[0].__value_##func .data.size(); \
  for (int _i = 0; _i < _n; ++_i) {\
    __perturb_matrix(##func [_i]); \
  }\
}
#define __perturb_matrix_dim2(func) {\
  int _n = _stat_memo[0].__value_##func.data.size(); \
  int _m = _stat_memo[0].__value_##func .data[0].size(); \
  for (int _i = 0; _i < _n; ++_i) {\
    for (int _j = 0; _j < _m; ++_j) {\
      __perturb_matrix(##func [_i][_j]); \
    }\
  }\
}

}

