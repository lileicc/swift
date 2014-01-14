/*
 * LWSamplerUrnBall.h
 *
 *  Created on: Nov 21, 2013
 *      Author: leili
 */
#pragma once
#include <string>
#include <vector>
#include <map>

namespace lwsampler {

struct Ball {
  std::string name;
};

struct Draw {
  std::string name;
};

struct Color {
  std::string name;
};

class LWSamplerUrnBall {
private:
  const static int num_color = 2;
  const static int num_draw = 10;

public:
  LWSamplerUrnBall();
  ~LWSamplerUrnBall();
  void sample(int n); // take n samples
  void printResult();
  std::map<int, double> getResult(); // the result is a mapping from int to probability

  Color color[num_color];
  Draw draw[num_draw];
  std::vector<Ball> ball;

private:
  double total_weight; // total weight
  double* weights; // weights for each possible world
  int* ans; // answer for the query
  int loops = 1000000; // number of samples, by default 1million
  int get_num_ball(); // get the number of ball for the current model, generate sample if not sampled
  int cur_loop; // currently sampling which possible world?
  int mark_num_ball; // what is sampling possible world number for #ball
  int num_ball; // number of balls
  std::vector<int> mark_truecolor; // i-th ball possible world number
  std::vector<int> value_truecolor; // value of i-th ball true color
  int get_truecolor(int b); // get the true color of the b-th ball
  void ensure_truecolor(int n); // ensure the true color has enough elements as number of ball
  int mark_balldrawn[num_draw]; // i-th balldraw possible world number
  int value_balldrawn[num_draw]; // value of the i-th balldraw, (i here corresponds to draw)
  int get_balldrawn(int d); // get the balldraw, generate sample if not sampled
  int mark_obscolor[num_draw]; // i-th obscolor possible world
  int value_obscolor[num_draw]; // value of the i-th obscolor (i here corresponds to draw)
  int get_obscolor(int d); // get the observed color for d-th draw, generate sample if not sampled
  double observe_obscolor(int d, int c); // set the observation color for d-th draw
  double likeli_obscolor(int d); // get the likelihood of the obscolor of the d-th draw
  std::vector<int> observed_obscolor; // observation for obscolor
  void init_observation(); // initialize the observation
  void sample();
};



} /* namespace lwsampler */
