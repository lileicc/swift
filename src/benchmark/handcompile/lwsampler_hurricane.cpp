/*
 * lwsampler_hurricane.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: yiwu
 *      Author: leili
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <cassert>
#include <complex>
#include <random>
#include <chrono>
#include <ctime>

#include "lwsampler_hurricane.h"

using namespace std;

namespace LWSAMPLER {
std::random_device rd;
//std::mt19937 gen(rd());
std::default_random_engine gen(rd());

const double eps = 1e-9;
const int Loops = 1000000;

inline int RND() {
  return ((rand() & 32767) << 15) + (rand() & 32767);
}

inline int uniformInt(int k) {
  return rand() % k; //RND() % k;
}

inline double uniformIntLikely(int k, int v) {
  return log(1.0 / k);
}

const double ratio = 1.0 / RAND_MAX;

std::uniform_real_distribution<> dis(0, 1);
inline double uniformDbl() {
  return dis(gen); //rand()*ratio;//uniformInt(100000001) * 1e-8;
}

inline int uniformWeight(const double* W, int n) { // W is accumulated
  double cur = uniformDbl();
  return lower_bound(W, W + n, cur) - W;
}

inline double uniformWeightLikely(const double*W, int n, int v) {
  if (v == 0)
    return log(W[0]);
  else
    return log(W[v] - W[v - 1]);
}

int cur_loop;
double total_weight;

class c_City {
public:
  string name;
} inst_city[2];
int city_n = 2;

class c_PrepLevel {
public:
  string name;
} inst_preplevel[2];
int preplevel_n = 2;

class c_DamageLevel {
public:
  string name;
} inst_damagelevel[2];
int damagelevel_n = 2;

void initDistinct() {
  inst_city[0].name = "A";
  inst_city[1].name = "B";
  inst_preplevel[0].name = "High";
  inst_preplevel[1].name = "Low";
  inst_damagelevel[0].name = "Severe";
  inst_damagelevel[1].name = "Mild";
}

int mark_first, ret_first;
int get_first() {
  if (mark_first == cur_loop)
    return ret_first;
  mark_first = cur_loop;
  int&ret = ret_first;
  ret = uniformInt(city_n);
  return ret;
}
;

double likely_first() {
  return uniformIntLikely(city_n, ret_first);
}
;

int mark_prep[2], ret_prep[2];
int prep_visit[2], prep_n;

/*
 random PrepLevel Prep(City c) {
 if (First == c) then ~ Categorical({High -> 0.5, Low -> 0.5})
 else ~ TabularCPD({Severe -> ~ Categorical({High -> 0.9, Low -> 0.1}),
 Mild -> ~ Categorical({High -> 0.1, Low -> 0.9})},
 Damage(First))
 };
 */
int get_damage(int);
int get_prep(int i) {
  if (mark_prep[i] == cur_loop)
    return ret_prep[i];
  mark_prep[i] = cur_loop;
  prep_visit[prep_n++] = i;
  int&ret = ret_prep[i];
  if (get_first() == i) {
    const double W[2] = { 0.5, 1.0 };
    ret = uniformWeight(W, 2);
  } else {
    switch (get_damage(get_first())) {
    case 0: {
      const double W[2] = { 0.9, 1.0 };
      ret = uniformWeight(W, 2);
    }
      break;
    case 1: {
      const double W[2] = { 0.1, 1.0 };
      ret = uniformWeight(W, 2);
    }
      break;
    }
  }
  return ret;
}
;

double likely_prep(int i) {
  int&ret = ret_prep[i];
  if (get_first() == i) {
    const double W[2] = { 0.5, 1.0 };
    return uniformWeightLikely(W, 2, ret);
  } else {
    switch (get_damage(get_first())) {
    case 0: {
      const double W[2] = { 0.9, 1.0 };
      return uniformWeightLikely(W, 2, ret);
    }
      break;
    case 1: {
      const double W[2] = { 0.1, 1.0 };
      return uniformWeightLikely(W, 2, ret);
    }
      break;
    }
  }
  return 0;
}
;

int mark_damage[2], ret_damage[2];
int damage_visit[2], damage_n;
/*
 random DamageLevel Damage(City c) {
 ~ TabularCPD({High -> ~ Categorical({Severe -> 0.2, Mild -> 0.8}),
 Low -> ~ Categorical({Severe -> 0.8, Mild -> 0.2})},
 Prep(c))
 };
 */
int get_damage(int i) {
  if (mark_damage[i] == cur_loop)
    return ret_damage[i];
  mark_damage[i] = cur_loop;
  damage_visit[damage_n++] = i;
  int& ret = ret_damage[i];
  switch (get_prep(i)) {
  case 0: {
    const double W[2] = { 0.2, 1.0 };
    return (ret = uniformWeight(W, 2));
  }
    break;
  case 1: {
    const double W[2] = { 0.8, 1.0 };
    return (ret = uniformWeight(W, 2));
  }
    break;
  }
  return 0;
}
;

double likely_damage(int i) {
  int& ret = ret_damage[i];
  switch (get_prep(i)) {
  case 0: {
    const double W[2] = { 0.2, 1.0 };
    return (uniformWeightLikely(W, 2, ret));
  }
    break;
  case 1: {
    const double W[2] = { 0.8, 1.0 };
    return (uniformWeightLikely(W, 2, ret));
  }
    break;
  }
  return 0;
}
;

double tag_damage(int i, int v) {
  // No Equivalence here
  // Directly Tagging is okay
  //get_damage(i);
  mark_damage[i] = cur_loop;
  damage_visit[damage_n++] = i;
  ret_damage[i] = v;
  return likely_damage(i);
}
;

int Ans[3][Loops + 1];
double Wei[Loops + 1];

void LWSample() {
  // Clear Weight
  Wei[cur_loop] = 0;
  prep_n = damage_n = 0;
  // Go from Evidence
  /*
   obs Damage(First) = Severe;
   */
  double &w = Wei[cur_loop];
  w += tag_damage(get_first(), 0);

  // Collect Query Answer
  /*
   query First;
   query Damage(A);
   query Damage(B);
   */
  Ans[0][cur_loop] = get_first();
  Ans[1][cur_loop] = get_damage(0);
  Ans[2][cur_loop] = get_damage(1);

  // Compute Weight

  //w += likely_first();
  //for(int i=0;i<damage_n;++i)
  //  w += likely_damage(damage_visit[i]);
  //for(int i=0;i<prep_n;++i)
  //  w += likely_prep(prep_visit[i]);

  w = exp(w);

  total_weight += w;
}

void OutputCity(int * ans, const char* buf) { // for City A or B
  double w[2] = { 0, 0 };
  for (int i = 1; i <= Loops; ++i)
    w[ans[i]] += Wei[i];
  printf("%s\n", buf);
  for (int i = 0; i < city_n; ++i) {
    w[i] /= total_weight;
    printf("   > %s : %.5lf\n", inst_city[i].name.c_str(), w[i]);
  }
}

void OutputDamage(int * ans, const char* buf) { // for City A or B
  double w[2] = { 0, 0 };
  for (int i = 1; i <= Loops; ++i)
    w[ans[i]] += Wei[i];
  printf("%s\n", buf);
  for (int i = 0; i < damagelevel_n; ++i) {
    w[i] /= total_weight;
    printf("   > %s : %.5lf\n", inst_damagelevel[i].name.c_str(), w[i]);
  }
}

void run() {

  srand((unsigned) time(0));
  
  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();

  initDistinct();
  for (cur_loop = 1; cur_loop <= Loops; ++cur_loop)
    LWSample();

  // Compute Answer
  OutputCity(Ans[0], "First: ");
  OutputDamage(Ans[1], "Damage(A): ");
  OutputDamage(Ans[2], "Damage(B): ");

  printf("++++++++++++++++++++++++++++++++\n");
  printf(" Sample Number: %d\n", Loops);
  std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
  printf(" Time Elapsed: %fs\n", elapsed.count());
}
}

