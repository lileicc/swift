/*
 * LWSamplerUrnBall.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: leili
 */

#include "LWSamplerUrnBall.h"
#include <random>
#include <cstdlib>
#include <cstring>

namespace lwsampler {

std::random_device rd;
std::default_random_engine gen(rd());
//std::mt19937_64 gen(rd());
std::poisson_distribution<int> poisson6(6.0);

/*
distinct Color Blue, Green;
distinct Draw Draw[10];
*/


/*
#Ball ~ Poisson(6);
*/
int LWSamplerUrnBall::get_num_ball() {
  if (mark_num_ball == cur_loop) return num_ball;
  mark_num_ball = cur_loop;
  num_ball = poisson6(gen);
  ensure_truecolor(num_ball);
  return num_ball;
}

void LWSamplerUrnBall::ensure_truecolor(int n) {
  mark_truecolor.resize(n);
  value_truecolor.resize(n);
}

/*
random Color TrueColor(Ball b) ~ Categorical({Blue -> 0.5, Green -> 0.5});
*/
std::discrete_distribution<int> cate1{ 0.5, 0.5 };
int LWSamplerUrnBall::get_truecolor(int b) {
  if (mark_truecolor[b] == cur_loop) return value_truecolor[b];
  mark_truecolor[b] = cur_loop;
  int&ret = value_truecolor[b];
  ret = cate1(gen);
  return ret;
}

/*
random Ball BallDrawn(Draw d) ~ UniformChoice({Ball b});
*/
int LWSamplerUrnBall::get_balldrawn(int d) {
  if (mark_balldrawn[d] == cur_loop) return value_balldrawn[d];
  mark_balldrawn[d] = cur_loop;
  int& ret = value_balldrawn[d];
  int n = get_num_ball();
  if (n == 0) ret = -1; // NULL
  else ret = rand() % n;
  return ret;
}

std::discrete_distribution<int> cate2{ 0.8, 0.2 };
std::discrete_distribution<int> cate3{ 0.2, 0.8 };
std::vector<double> cate2_prob = cate2.probabilities();
std::vector<double> cate3_prob = cate3.probabilities();
/*
random Color ObsColor(Draw d) {
if (BallDrawn(d) != null)
then ~ TabularCPD({Blue -> ~ Categorical({Blue -> 0.8, Green -> 0.2}),
                    Green -> ~ Categorical({Blue -> 0.2, Green -> 0.8})},
                  TrueColor(BallDrawn(d)))
};
*/
int LWSamplerUrnBall::get_obscolor(int d) {
  if (mark_obscolor[d] == cur_loop) return value_obscolor[d];
  mark_obscolor[d]=cur_loop;
  int&ret = value_obscolor[d];
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

double LWSamplerUrnBall::observe_obscolor(int d, int c) {
  mark_obscolor[d]=cur_loop;
  value_obscolor[d] = c;
  return likeli_obscolor(d);
}

void LWSamplerUrnBall::printResult() {
  if (cur_loop != loops) {
    printf("please sample first!\n");
    return;
  }
  printf("Samples = %d\n", loops - 1);
  printf("++++++++++++++++++++++++++++++++++\n");
  printf("Result for #{Ball b}:\n");
  std::map<int, double> result = getResult();
  for (auto it = result.begin(); it != result.end(); it++) {
    printf("  > %d : %.5lf\n", it->first, it->second);
  }
}

std::map<int, double> LWSamplerUrnBall::getResult() {
  std::map<int, double> acc;
  for (int i = 1; i < loops; ++i)
//    if (weights[i] > 1e-9)
      acc[ans[i]] += weights[i];
  for (auto it = acc.begin(); it != acc.end(); it++) {
    it->second = (it->second) / total_weight;
  }
  return acc;
}

void LWSamplerUrnBall::sample() {
  // check evidence
  double w = 1;
  for (size_t i = 0; i < observed_obscolor.size(); ++i)
    w *= observe_obscolor(i, observed_obscolor[i]);

  // get query
  /*
  query #{Ball b};
  */
  ans[cur_loop] = get_num_ball();

  total_weight += w;
  weights[cur_loop] = w;
}

LWSamplerUrnBall::LWSamplerUrnBall() : num_ball(0) {
  cur_loop = -1;
  total_weight = 0;
  ans = NULL;
  weights = NULL;
  init_observation();
}

LWSamplerUrnBall::~LWSamplerUrnBall() {
  delete[] ans;
  delete[] weights;
}

double LWSamplerUrnBall::likeli_obscolor(int d) {
  int& val = value_obscolor[d];
  double w = 1;
  int b = get_balldrawn(d);
  if (b != -1) {
    switch (get_truecolor(b)) {
    case 0: // Blue
      w = cate2_prob[val];
      break;
    case 1: // Green
      w = cate3_prob[val];
      break;
    }
  } else w = 0;
  return w;
}

void LWSamplerUrnBall::sample(int n) {
  delete [] ans;
  delete [] weights;
  loops = n + 1;
  ans = new int[loops];
  cur_loop = -1;
  weights = new double[loops];
  memset(weights, 0, sizeof(weights));
  memset(ans, 0, sizeof(ans));
  total_weight = 0;
  mark_num_ball = 0;
  num_ball = -1;
  for (cur_loop = 1; cur_loop < loops; ++ cur_loop)
    sample();
}

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
void LWSamplerUrnBall::init_observation() {
  observed_obscolor = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
}

} /* namespace lwsampler */
