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

// Utility Functions
template<class T>
inline void _util_init_range(std::vector<T>&vals, T st, T en) {
  for (T i = st; i <= en; ++ i)
    vals.push_back(i);
}

inline void _util_update_range(std::vector<int>&vals, int n) {
  if (n > vals.size()) {
    for (int i = vals.size(); i < n; ++ i)
      vals.push_back(i);
  } else
    vals.resize(n);
}

inline int _util_calc_reference_diff(NumberVar* numvar, int from, int to) {
  int prop_size = numvar->get_property_size();
  std::vector<int>& refer = numvar->refer_cnt;
  int ret = 0;
  if (refer[from] == 1) ret -= prop_size;
  if (refer[to] == 0) ret += prop_size;
  return ret;
}

inline void _util_clear_reference(NumberVar* numvar, BayesVar<int>*ptr, int val) {
  numvar->dep_var.erase(ptr);
  if (--numvar->refer_cnt[val] == 0) {
    std::vector<int>& pos = numvar->obj_pos;
    std::vector<int>& lis = numvar->active_obj;
    int t = pos[val];
    lis[t] = lis.back();
    pos[lis.back()] = t;
    lis.pop_back();
    pos[val] = -1;
    // fully clear all the properties related to this object
    numvar->clear_prop_arg(val);
  }
}

inline void _util_update_reference(NumberVar* numvar, BayesVar<int>*ptr, int val) {
  numvar->dep_var.insert(ptr);
  if (++numvar->refer_cnt[val] == 1) {
    std::vector<int>& pos = numvar->obj_pos;
    std::vector<int>& lis = numvar->active_obj;
    pos[val] = lis.size();
    lis.push_back(val);
    // instantiate all the properties
    numvar->ensure_support_prop_arg(val);
  }
}

template<class T>
inline void _util_set_evidence(BayesVar<T>* ptr, T val) {
  ptr->getval();
  ptr->val = val;
  if (!ptr->is_obs) {
    ptr->is_obs = true;

    // Remove it from active var
    remove_var_from_list(ptr);
  }
}

template<class T>
inline void _util_update_evidence(BayesVar<T>* ptr, bool flag) {
  if (ptr->is_obs == flag) return ;
  if (flag) {
    if (!ptr->is_active) ptr->getval();
    // A un-observed var become observed
    remove_var_from_list(ptr);
  }
  else {
    // an observed var become un-observed
    add_var_to_list(ptr);
  }
  ptr->is_obs = flag;
}

}
