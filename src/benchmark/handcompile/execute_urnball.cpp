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
#include <chrono>

using namespace std;
int main(int argc, char* argv[]) {

  int N = 1000000; // number of samples
  if (argc > 2) {
    N = atoi(argv[1]);
  }

  URNBALL_REJ::run(N);

  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();

  lwsampler::LWSamplerUrnBall lwsampler;
  lwsampler.sample(N);
  printf("sampling using LWSampler\n");
  lwsampler.printResult();
  std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
  printf("Time Elapsed = %fs\n", elapsed.count());
  return 0;
}
