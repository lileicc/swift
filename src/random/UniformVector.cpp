/*
 * UniformVector.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: yiwu
 */
#include <cmath>
#include <algorithm>
#include <cassert>
#include "UniformVector.h"

namespace swift {
namespace random {

UniformVector::UniformVector() :prod(1), logprod(0) {
  a.clear(); b.clear(); dists.clear();
}

UniformVector::~UniformVector() {
}

void UniformVector::init(mat lo, mat hi) {
  assert(lo.n_elem == hi.n_elem);
  int n = lo.n_elem;
  for (int i = 0; i < n; ++i) {
    dists.push_back(std::uniform_real_distribution<double>(lo[i], hi[i]));
    prod *= 1.0 / (hi[i] - lo[i]);
    logprod -= std::log(hi[i] - lo[i]);
    a.push_back(lo[i]);
    b.push_back(hi[i]);
  }
  retvec.reshape(n, 1);
}

void UniformVector::init(mat box) {
  assert(box.n_cols == 2);
  int n = box.n_rows;
  for (int i = 0; i < n; ++i) {
    dists.push_back(std::uniform_real_distribution<double>(box(i, 0), box(i, 1)));
    prod *= 1.0 / (box(i, 0) - box(i, 1));
    logprod -= std::log(box(i, 0) - box(i, 1));
    a.push_back(box(i,0));
    b.push_back(box(i,1));
  }
  retvec.reshape(n, 1);
}

mat UniformVector::gen() {
  for (size_t i = 0; i < dists.size(); ++i) {
    retvec[i] = dists[i](engine);
  }
  return retvec;
}

double UniformVector::likeli(const mat& x) {
  if (x.n_elem != dists.size()) return 0;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return 0;
  }
  return prod;
}

double UniformVector::loglikeli(const mat& x) {
  if (x.n_elem != dists.size()) return -INFINITY;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return -INFINITY;
  }
  return logprod;
}

} /* namespace random */
} /* namespace swift */
