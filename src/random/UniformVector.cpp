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
  :dist(0.0,1.0), prod(1), logprod(0),
   is_prod_ok(false), is_logprod_ok(false) {
}

UniformVector::~UniformVector() {
}

void UniformVector::init(const arma::mat& lo, const arma::mat& hi) {
  assert(lo.n_elem == hi.n_elem);
  int n = lo.n_elem;
  a.resize(n); b.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i] = lo[i];
    b[i] = hi[i];
  }
  retvec.set_size(n, 1);
  is_prod_ok=false;
  is_logprod_ok = false;
}

void UniformVector::init(const arma::mat& box) {
  assert(box.n_cols == 2);
  int n = box.n_rows;
  a.resize(n); b.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i] = box(i,0);
    b[i] = box(i,1);
  }
  retvec.set_size(n, 1);
  is_prod_ok=false;
  is_logprod_ok=false;
}

arma::mat UniformVector::gen() {
  for (size_t i = 0; i < a.size(); ++i) {
    retvec[i] = dist(engine) * (b[i] - a[i]) + a[i];
  }
  return retvec;
}

double UniformVector::likeli(const arma::mat& x) {
  if (x.n_elem != a.size()) return 0;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return 0;
  }
  if(!is_prod_ok) {
    prod = 1;
    for(size_t i = 0; i < a.size(); ++ i) {
      prod *= 1.0 / (b[i] - a[i]);
    }
    is_prod_ok=true;
  }
  return prod;
}

double UniformVector::loglikeli(const arma::mat& x) {
  if (x.n_elem != a.size()) return -INFINITY;
  for (size_t i = 0; i < a.size(); ++i) {
    if (x[i] < a[i] - 1e12 || x[i] > b[i] + 1e-12)
      return -INFINITY;
  }
  if(!is_logprod_ok) {
    logprod = 1;
    for(size_t i = 0; i < a.size(); ++ i) {
      logprod -= std::log(b[i] - a[i]);
    }
    is_logprod_ok=true;
  }
  return logprod;
}

} /* namespace random */
} /* namespace swift */
