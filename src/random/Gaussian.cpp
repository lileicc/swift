/*
 * Gaussian.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: yiwu
 */
 
#include <cmath>
#include "Gaussian.h"

namespace swift {
namespace random {

Gaussian::Gaussian() :
    dist(0.0, 1.0), mean(0.0), stddev(1.0) {
}

Gaussian::~Gaussian() {
}

void Gaussian::init(double mean, double var) {
  this->mean = mean;
  this->stddev = std::sqrt(var);
  coef = 1.0 / (stddev * std::sqrt(PI * 2));
  log_coef = - std::log(stddev * std::sqrt(PI * 2));
  scale = - 1.0 / (2 * stddev * stddev);
}

double Gaussian::gen() {
  return dist(engine) * stddev + mean;
}

double Gaussian::likeli(const double& x) {
  return coef * std::exp(scale * (x - mean) * (x - mean));
}

double Gaussian::loglikeli(const double& x) {
  return scale * (x - mean) * (x - mean) + log_coef;
}

} /* namespace random */
} /* namespace swift */
