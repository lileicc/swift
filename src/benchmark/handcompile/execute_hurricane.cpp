/*
 * execute.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: yiwu
 */
#include <cstdlib>
#include <iostream>
#include <random>
#include <cstdio>

#include "lwsampler_hurricane.h"
#include "rejsampler_hurricane.h"

using namespace std;
int main() {

  LWSAMPLER::run();

  REJECTSAMPLER::run();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  double a = dis(gen);
  std::cout<<a<<std::endl;

  printf("%.2lf\n", a);

  std::system("pause");
  return 0;
}
