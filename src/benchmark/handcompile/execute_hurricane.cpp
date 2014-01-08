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
//  std::system("pause");
  return 0;
}
