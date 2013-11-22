/*
 * execute_urnball.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: leili
 */

#include "rejsampler_urnball.h"
#include "LWSamplerUrnBall.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <cstdio>
using namespace std;
int main() {
  URNBALL_REJ::run();

  int t = clock();

  lwsampler::LWSamplerUrnBall lwsampler;
  lwsampler.sample(1000000);
  printf("sampling using LWSampler\n");
  lwsampler.printResult();
  t = clock() - t;
  printf("Time Elapsed = %d.%03ds\n", t/1000000, t%1000000);
  return 0;
}
