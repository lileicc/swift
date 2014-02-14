/*
 * LWSamplerCSI.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: yiwu
 */

#include "LWSamplerCSI.h"
#include <random>
#include <cstdlib>
#include <cstring>
#include <chrono>

namespace lwsampler {

std::random_device rd;
std::default_random_engine gen(rd());
//std::mt19937_64 gen(rd());
std::bernoulli_distribution BoolDistr1(0.3);
std::bernoulli_distribution BoolDistr2(0.9);
std::bernoulli_distribution BoolDistr3(0.1);
std::bernoulli_distribution BoolDistr4(0.8);
std::bernoulli_distribution BoolDistr5(0.2);
std::bernoulli_distribution BoolDistr6(0.8);
std::bernoulli_distribution BoolDistr7(0.2);

/*
random Boolean U ~ BooleanDistrib(0.3);
*/
bool LWSamplerCSI::get_U() {
  if (mark_U == cur_loop) return value_U;
  mark_U = cur_loop;
  bool& ret = value_U;
  ret = BoolDistr1(gen);
  return ret;
}

/*
random Boolean V ~ BooleanDistrib(0.9);
*/
bool LWSamplerCSI::get_V() {
  if (mark_V == cur_loop) return value_V;
  mark_V = cur_loop;
  bool& ret = value_V;
  ret = BoolDistr2(gen);
  return ret;
}

/*
random Boolean W ~ BooleanDistrib(0.1);
*/
bool LWSamplerCSI::get_W() {
  if(mark_W == cur_loop) return value_W;
  mark_W = cur_loop;
  bool& ret = value_W;
  ret = BoolDistr3(gen);
  return ret;
}

/*
random Boolean X {
    if U then ~ TabularCPD({true -> ~ BooleanDistrib(0.8),
       	      		    false -> ~ BooleanDistrib(0.2)}, W)
    else ~ TabularCPD({true -> ~ BooleanDistrib(0.8),
    	   	       false -> ~ BooleanDistrib(0.2)}, V)
};
*/
bool LWSamplerCSI::get_X() {
  if(mark_X == cur_loop) return value_X;
  mark_X = cur_loop;
  bool& ret = value_X;
  if(get_U()) {
    switch(get_W()) {
      case true:
        ret = BoolDistr4(gen);
        break;
      case false:
        ret = BoolDistr5(gen);
        break;
    }
  } else {
    switch(get_V()) {
      case true:
        ret = BoolDistr6(gen);
        break;
      case false:
        ret = BoolDistr7(gen);
        break;
    }
  }
  return ret;
}

void LWSamplerCSI::printResult() {
  if (cur_loop != loops) {
    printf("please sample first!\n");
    return;
  }
  printf("Samples = %d\n", loops - 1);
  printf("++++++++++++++++++++++++++++++++++\n");
  printf("Result for X:\n");
  std::map<bool, double> result = getResult();
  for (auto it = result.begin(); it != result.end(); it++) {
    printf("  > %d : %.5lf\n", it->first, it->second);
  }
}

std::map<bool, double> LWSamplerCSI::getResult() {
  std::map<bool, double> acc;
  for (int i = 1; i < loops; ++i)
//    if (weights[i] > 1e-9)
      acc[ans[i]] += weights[i];
  for (auto it = acc.begin(); it != acc.end(); it++) {
    it->second = (it->second) / total_weight;
  }
  return acc;
}

void LWSamplerCSI::sample() {
  // check evidence
  double w = 1;
  // get query
  /*
  query X;
  */
  ans[cur_loop] = get_X();

  total_weight += w;
  weights[cur_loop] = w;
}

LWSamplerCSI::LWSamplerCSI() {
  cur_loop = -1;
  total_weight = 0;
  ans = NULL;
  weights = NULL;
}

LWSamplerCSI::~LWSamplerCSI() {
  delete[] ans;
  delete[] weights;
}

void LWSamplerCSI::sample(int n) {
  delete [] ans;
  delete [] weights;
  loops = n + 1;
  ans = new int[loops];
  cur_loop = -1;
  weights = new double[loops];
  memset(weights, 0, sizeof(weights));
  memset(ans, 0, sizeof(ans));
  total_weight = 0;
  for (cur_loop = 1; cur_loop < loops; ++ cur_loop)
    sample();
}

} /* namespace lwsampler */


int main(int argc, char* argv[]) {
  int N = 1000000; // number of samples
  if (argc > 2) {
    N = atoi(argv[1]);
  }
  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();
  
  lwsampler::LWSamplerCSI lwsampler;
  lwsampler.sample(N);
  printf("sampling using LWSampler\n");
  lwsampler.printResult();
  std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
  printf("Time Elapsed = %fs\n", elapsed.count());
  return 0;
}