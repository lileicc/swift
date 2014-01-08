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
int main(int argc, char* argv[]) {

  int N = 1000000; // number of samples
  if (argc > 2) {
    N = atoi(argv[1]);
  }

  URNBALL_REJ::run(N);

  int t = clock();

  lwsampler::LWSamplerUrnBall lwsampler;
  lwsampler.sample(N);
  printf("sampling using LWSampler\n");
  lwsampler.printResult();
  t = clock() - t;
  printf("Time Elapsed = %d.%03ds\n", t/1000000, t%1000000);
  return 0;
}
