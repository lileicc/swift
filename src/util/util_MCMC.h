//
//  util_MCMC.h
//  swift-project
//  util functions for MCMC algorithms (Parental MH, Gibbs)
//
//  Created by Yi Wu on 4/15/15.
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

#include "MCMC.h"
#include "DynamicTable.h"

namespace swift {

// Garbage Collection for single object
inline void _free_obj(MCMCObject* obj) {
  if (obj != NULL) delete obj;
}

// Garbage Collection for objects stored in multi-dimensional tables
template <typename _T, size_t _dim>
struct _mdvector_ptr {
  //  static_assert(_dim >= 1, "entering general _mdvector_ptr with _dim ");
  typedef std::vector<typename _mdvector_ptr<_T, _dim - 1>::type> type;

  static void _free(typename _mdvector_ptr<_T, _dim>::type & data) {
    for (auto & d : data) {
      _mdvector_ptr<_T, _dim - 1>::_free(d);
    }
  };
};

template <typename _T>
struct _mdvector_ptr<_T, 1> {
  typedef std::vector<_T*> type;
  static void _free(type & data) {
    for (auto& d : data) {
      if (d != NULL) delete d;
    }
  };
};

template <typename _T>
struct _mdvector_ptr<_T, 0> {
  typedef _T* type;
};

// Clear Dynamic Tables storing pointers
template <typename _T, size_t _dim>
inline void _free_obj(DynamicTable<_T*, _dim>& vec) {
  _mdvector_ptr<_T, _dim>::_free(vec.data);
}

}
