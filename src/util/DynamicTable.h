/*
 * DynamicTable.h
 *
 *  Created on: Feb 18, 2014
 *      Author: leili
 */

#pragma once

#include <vector>

template <typename _T, size_t _dim>
struct _mdvector {
//  static_assert(_dim > 1, "entering general _mdvector with _dim ");
  typedef std::vector<typename _mdvector<_T, _dim - 1>::type> type;
  /**
   * resize the underlying multi-dimensional vector in the specified dimension
   *
   * Implementation details:
   *   it will only increase size, but will never reduce the actual size.
   * @param data
   * @param dim       the dimension on which it needs resizing (starts at 0)
   * @param sz        the new sz of the dimension
   */
  static void _resize(typename _mdvector<_T, _dim>::type & data, size_t dim, size_t sz) {
    if (dim == 0)
      data.resize(sz);
    else {
      for (auto & a : data) {
        _mdvector<_T, _dim-1>::_resize(a, dim - 1, sz);
      }
    }
  };
};

template <typename _T>
struct _mdvector<_T, 1> {
  typedef std::vector<_T> type;
  static void _resize(type & data, size_t dim, size_t sz) {
    if (dim == 0)
      data.resize(sz);
  };
};

template <typename _T>
struct _mdvector<_T, 0> {
  typedef _T type;
};

/**
 * Multi-dimensional dynamic table.
 * It will adaptively grow the size of each dimension.
 */
template <typename _T, size_t _dim>
class DynamicTable {
public:
  DynamicTable() : maxsize(_dim, 0) {
  };
  ~DynamicTable() {};

  /**
   * resize this multi-dimensional table in the specified dimension
   *
   * Implementation details:
   *   it will only increase size, but will never reduce the actual size.
   * @param dim     the dimension on which it needs resizing (starts at 0)
   * @param sz      the new sz of the dimension
   */
  void resize(size_t dim, size_t sz) {
    if (dim >= maxsize.size() || sz <= maxsize[dim])
      return;
    _mdvector<_T, _dim>::_resize(data, dim, sz);
    if ((_dim > dim + 1) && (maxsize[dim] == 0)) {
      for (size_t i = dim+1; (i < _dim) && (maxsize[i] > 0); i++) {
        _mdvector<_T, _dim>::_resize(data, i, maxsize[i]);
      }
    }
    maxsize[dim] = sz;
  };
  
  /**
   *  get the i-th content
   *
   *  @param i the value indicated by i
   *  @return
   */
  inline typename _mdvector<_T, _dim-1>::type& operator [](size_t i) {
    return data[i];
  }
  
  typename _mdvector<_T, _dim>::type data;
  
private:
  std::vector<size_t> maxsize;
};

