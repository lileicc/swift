/*
 * rejsampler_urnball.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: yiwu
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <ctime>
#include "rejsampler_urnball.h"

using namespace std;

namespace URNBALL_REJ {

std::default_random_engine gen;
std::poisson_distribution<int> poisson6(6.0);

/*
distinct Color Blue, Green;
distinct Draw Draw[10];
*/

int cur_loop;

/*
#Ball ~ Poisson(6);
*/
int mark_ball_n;
int ball_n;
int get_ball_n() {
  if (mark_ball_n == cur_loop) return ball_n;
  mark_ball_n = cur_loop;
  ball_n = poisson6(gen);
  return ball_n;
}

std::discrete_distribution<int> cate1{ 0.5, 0.5 };
/*
random Color TrueColor(Ball b) ~ Categorical({Blue -> 0.5, Green -> 0.5});
*/
vector<int> mark_truecolor;
vector<int> ret_truecolor;
int get_truecolor(int b) {
  // get address
  if (b >= mark_truecolor.size()) {
    mark_truecolor.resize(b+1);
    ret_truecolor.resize(b+1);
  }
  if (mark_truecolor[b] == cur_loop) return ret_truecolor[b];
  mark_truecolor[b] = cur_loop;
  int&ret = ret_truecolor[b];
  ret = cate1(gen);
  return ret;
}

/*
random Ball BallDrawn(Draw d) ~ UniformChoice({Ball b});
*/
int mark_balldrawn[10];
int ret_balldrawn[10];
int get_balldrawn(int d) {
  if (mark_balldrawn[d] == cur_loop)return ret_balldrawn[d];
  mark_balldrawn[d] = cur_loop;
  int&ret = ret_balldrawn[d];
  int n = get_ball_n();
  if (n == 0) ret = -1; // NULL
  else ret = rand() % get_ball_n();
  return ret;
}

std::discrete_distribution<int> cate2{ 0.8, 0.2 };
std::discrete_distribution<int> cate3{ 0.2, 0.8 };
/*
random Color ObsColor(Draw d) {
if (BallDrawn(d) != null)
then ~ TabularCPD({Blue -> ~ Categorical({Blue -> 0.8, Green -> 0.2}),
                    Green -> ~ Categorical({Blue -> 0.2, Green -> 0.8})},
                  TrueColor(BallDrawn(d)))
};
*/
int mark_obscolor[10];
int ret_obscolor[10];
int get_obscolor(int d) {
  if (mark_obscolor[d] == cur_loop) return ret_obscolor[10];
  mark_obscolor[d]=cur_loop;
  int&ret = ret_obscolor[d];
  if (get_balldrawn(d) != -1) {
    switch (get_truecolor(get_balldrawn(d))) {
    case 0: // Blue
      ret = cate2(gen);
      break;
    case 1: // Green
      ret = cate3(gen);
      break;
    }
  } else ret = -1;
  return ret;
}

const int Loops = 10000000;

double total_weight;
double Wei[Loops + 1];
int ans[Loops + 1];
int valid;

void single_sample() {
  // check evidence
  /*
  obs ObsColor(Draw[0]) = Blue;
  obs ObsColor(Draw[1]) = Green;
  obs ObsColor(Draw[2]) = Blue;
  obs ObsColor(Draw[3]) = Green;
  obs ObsColor(Draw[4]) = Blue;
  obs ObsColor(Draw[5]) = Green;
  obs ObsColor(Draw[6]) = Blue;
  obs ObsColor(Draw[7]) = Green;
  obs ObsColor(Draw[8]) = Blue;
  obs ObsColor(Draw[9]) = Green;
  */
  if (get_obscolor(0) != 0) return;
  if (get_obscolor(1) != 1) return;
  if (get_obscolor(2) != 0) return;
  if (get_obscolor(3) != 1) return;
  if (get_obscolor(4) != 0) return;
  if (get_obscolor(5) != 1) return;
  if (get_obscolor(6) != 0) return;
  if (get_obscolor(7) != 1) return;
  if (get_obscolor(8) != 0) return;
  if (get_obscolor(9) != 1) return;

  valid += 1;
  double w;

  // get query
  /*
  query #{Ball b};
  */
  ans[cur_loop] = get_ball_n();

  w = 1;

  total_weight += w;
  Wei[cur_loop] = w;
}

void OutputInt(int* ans, const char * buf) {
  map<int,double> acc;
  for (int i=1;i<=Loops;++i)
  if (Wei[i] > 1e-9)
    acc[ans[i]] += Wei[i];
  printf("Result of %s :\n", buf);
  for (map<int, double>::iterator it = acc.begin(); it != acc.end(); it++) {
    printf("  > %d : %.5lf\n", it->first, it->second / total_weight);
  }
}

void run() {

  int t = clock();

  // Init
  memset(Wei, 0, sizeof(Wei));
  total_weight = 0;
  valid = 0;

  for (cur_loop = 1; cur_loop <= Loops; ++ cur_loop)
    single_sample();

  // Output Consistent Rate
  printf("Samples = %d\n", Loops);
  printf("Consistent Rate = %.5lf\n", (double)valid / Loops);
  printf("++++++++++++++++++++++++++++++++++\n");

  // Output Result
  OutputInt(ans, "#{Ball b}");

  t = clock() - t;
  printf("Time Elapsed = %d.%03ds\n", t/1000, t%1000);
}

}


