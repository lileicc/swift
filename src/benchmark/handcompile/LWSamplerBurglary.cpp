//
//  LWSamplerBurglary.cpp
//  swift
//
//  Created by Lei Li on 2/9/14.
//  Copyright (c) 2014 Lei Li. All rights reserved.
//

#include <random>
#include <chrono>
#include "LWSamplerBurglary.h"


namespace lwsampler {
  
std::default_random_engine gen;
  
std::bernoulli_distribution dist1(0.001);
std::bernoulli_distribution dist2(0.002);
  
inline lwsampler::LWSamplerBurglary::LWSamplerBurglary() {
}

inline lwsampler::LWSamplerBurglary::~LWSamplerBurglary() {
}

void lwsampler::LWSamplerBurglary::sample(int n) {
  total_weight = 0;
  loops = n + 1;
  mark_alarm = -1;
  mark_burglary = -1;
  mark_earthquake = -1;
  mark_johncalls = -1;
  mark_marycalls = -1;
  for (cur_loop = 1; cur_loop < loops; cur_loop++) {
    sample();
  }
}

void lwsampler::LWSamplerBurglary::printResult() {
  if (cur_loop != loops) {
    printf("please sample first!\n");
    return;
  }
  printf("Samples = %d\n", loops - 1);
  printf("++++++++++++++++++++++++++++++++++\n");
  printf("Result for Burglary:\n");
  std::map<bool, double> result = getResult();
  printf("  > false: %.5lf\n", result[false]);
  printf("  > true:  %.5lf\n", result[true]);
}

std::map<bool, double> lwsampler::LWSamplerBurglary::getResult() {
  std::map<bool, double> res;
  res[true] = 0;
  res[false] = 0;
  for (int i = 0; i < ans.size(); i++) {
    res[ans[i]] += weights[i];
  }
  res[true] /= total_weight;
  res[false] /= total_weight;
  return res;
}

bool lwsampler::LWSamplerBurglary::get_burglary() {
  if (mark_burglary == cur_loop) return value_burglary;
  value_burglary = dist1(gen);
  mark_burglary = cur_loop;
  return value_burglary;
}

bool lwsampler::LWSamplerBurglary::get_earthquake() {
  if (mark_earthquake == cur_loop) return value_earthquake;
  value_earthquake = dist2(gen);
  mark_earthquake = cur_loop;
  return value_earthquake;
}
//
//  random Boolean Alarm {
//    if Burglary then
//      if Earthquake then
//        ~ BooleanDistrib(0.95)
//        else
//          ~ BooleanDistrib(0.94)
//          else
//            if Earthquake then
//              ~ BooleanDistrib(0.29)
//              else
//                ~ BooleanDistrib(0.001)  
//                };
std::bernoulli_distribution dist3(0.95);
std::bernoulli_distribution dist4(0.94);
std::bernoulli_distribution dist5(0.29);
std::bernoulli_distribution dist6(0.001);
bool lwsampler::LWSamplerBurglary::get_alarm() {
  if (mark_alarm == cur_loop) return value_alarm;
  if (get_burglary()) {
    if (get_earthquake()) {
      value_alarm = dist3(gen);
    } else {
      value_alarm = dist4(gen);
    }
  } else {
    if (get_earthquake()) {
      value_alarm = dist5(gen);
    } else {
      value_alarm = dist6(gen);
    }
  }
  mark_alarm = cur_loop;
  return value_alarm;
}
//
//  random Boolean JohnCalls
//	if Alarm then
//	  ~ BooleanDistrib(0.9)
//    else
//      ~ BooleanDistrib(0.05);
std::bernoulli_distribution dist7(0.9);
std::vector<double> weight7 = {0.1, 0.9};
std::bernoulli_distribution dist8(0.05);
std::vector<double> weight8 = {0.95, 0.05};
bool lwsampler::LWSamplerBurglary::get_johncalls() {
  if (mark_johncalls == cur_loop) return value_johncalls;
  if (get_alarm()) {
    value_johncalls = dist7(gen);
  } else {
    value_johncalls = dist8(gen);
  }
  mark_johncalls = cur_loop;
  return value_johncalls;
}
//  random Boolean MaryCalls
//  if Alarm then
//    ~ BooleanDistrib(0.7)
//    else
//      ~ BooleanDistrib(0.01);
std::bernoulli_distribution dist9(0.7);
std::vector<double> weight9 = {0.3, 0.7};
std::bernoulli_distribution dist10(0.01);
std::vector<double> weight10 = {0.99, 0.01};
bool lwsampler::LWSamplerBurglary::get_marycalls() {
  if (mark_marycalls == cur_loop) return value_marycalls;
  if (get_alarm()) {
    value_marycalls = dist9(gen);
  } else {
    value_marycalls = dist10(gen);
  }
  mark_marycalls = cur_loop;
  return value_marycalls;
}

double lwsampler::LWSamplerBurglary::likeli_johncalls() {
  if (get_alarm()) {
    return value_johncalls ? weight7[1] : weight7[0];
  } else {
    return value_johncalls ? weight8[1] : weight8[0];
  }
}

double lwsampler::LWSamplerBurglary::likeli_marycalls() {
  if (get_alarm()) {
    return value_marycalls ? weight9[1] : weight9[0];
  } else {
    return value_marycalls ? weight10[1] : weight10[0];
  }
}

double lwsampler::LWSamplerBurglary::observe_johncalls(bool v) {
  value_johncalls = v;
  mark_johncalls = cur_loop;
  return likeli_johncalls();
}

double lwsampler::LWSamplerBurglary::observe_marycalls(bool v) {
  value_marycalls = v;
  mark_marycalls = cur_loop;
  return likeli_marycalls();
}

double lwsampler::LWSamplerBurglary::set_evidence() {
  double w = 1;
  w = observe_johncalls(true);
  w *= observe_marycalls(true);
  return w;
}

void lwsampler::LWSamplerBurglary::sample() {
  double w;
  w = set_evidence();
  ans.push_back(get_burglary());
  weights.push_back(w);
  total_weight += w;
}
  
}

int main(int argc, char* argv[]) {
  int N = 1000000; // number of samples
  if (argc > 2) {
    N = atoi(argv[1]);
  }
  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();
 
  lwsampler::LWSamplerBurglary lwsampler;
  lwsampler.sample(N);
  printf("sampling using LWSampler\n");
  lwsampler.printResult();
  std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
  printf("Time Elapsed = %fs\n", elapsed.count());
  return 0;
}
