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

UniformVector::UniformVector()
  :dist(0.0,1.0), prod(1), logprod(0) {
  a.clear(); b.clear();
}

UniformVector::~UniformVector() {
}

void UniformVector::init(arma::mat lo, arma::mat hi) {
  assert(lo.n_elem == hi.n_elem);
  int n = lo.n_elem;
  a.resize(n); b.resize(n);
  for (int i = 0; i < n; ++i) {
    prod *= 1.0 / (hi[i] - lo[i]);
    logprod -= std::log(hi[i] - lo[i]);
    a[i] = lo[i];
    b[i] = hi[i];
  }
  retvec.set_size(n, 1);
}

void UniformVector::init(arma::mat box) {
  assert(box.n_cols == 2);
  int n = box.n_rows;
  a.resize(n); b.resize(n);
  for (int i = 0; i < n; ++i) {
    dists.push_back(std::uniform_real_distribution<double>(box(i, 0), box(i, 1)));
    prod *= 1.0 / (box(i, 0) - box(i, 1));
    logprod -= std::log(box(i, 0) - box(i, 1));
    a[i] = box(i,0);
    b[i] = box(i,1);
  }
  retvec.set_size(n, 1);
}

arma::mat UniformVector::gen() {
  for (size_t i = 0; i < dists.size(); ++i) {
    retvec[i] = dists(engine) * (b[i] - a[i]) + a[i];
  }
  return retvec;
}

double UniformVector::likeli(const arma::mat& x) {
  if (x.n_elem != dists.size()) return 0;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return 0;
  }
  return prod;
}

double UniformVector::loglikeli(const arma::mat& x) {
  if (x.n_elem != dists.size()) return -INFINITY;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return -INFINITY;
  }
  return logprod;
}

} /* namespace random */
} /* namespace swift */
