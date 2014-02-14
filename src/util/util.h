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

inline void resize(std::vector<int> & x, size_t id, size_t sz){
  if (id == 0) {
    // resize the first dimension
    if (x.size() > 0)
      x.resize(sz, x[0]);
    else
      x.resize(sz);
  }
}

inline void resize(std::vector<std::vector<int> > & x, size_t id, size_t sz){
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
  }
}

inline void resize(std::vector<std::vector<std::vector<int> > > & x, size_t id, size_t sz){
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

inline void resize(std::vector<double> & x, size_t id, size_t sz){
  if (id == 0) {
    // resize the first dimension
    if (x.size() > 0)
      x.resize(sz, x[0]);
    else
      x.resize(sz);
  }
}

inline void resize(std::vector<std::vector<double> > & x, size_t id, size_t sz){
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
  }
}

inline void resize(std::vector<std::vector<std::vector<double> > > & x, size_t id, size_t sz){
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

inline void resize(std::vector<bool> & x, size_t id, size_t sz){
  if (id == 0) {
    // resize the first dimension
    if (x.size() > 0)
      x.resize(sz, x[0]);
    else
      x.resize(sz);
  }
}

inline void resize(std::vector<std::vector<bool> > & x, size_t id, size_t sz){
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
  }
}

inline void resize(std::vector<std::vector<std::vector<bool> > > & x, size_t id, size_t sz){
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
