/*
 * LWSamplerUrnBall.h
 *
 *  Created on: Nov 21, 2013
 *      Author: leili
 */

#pragma once

#include <string>

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
public:
  LWSamplerUrnBall();
  ~LWSamplerUrnBall();
  const int num_color = 2;
  const int num_draw = 10;
  int num_ball;

  Color color[num_color];
  Draw draw[num_draw];
  std::vector<Ball> ball;
};



} /* namespace lwsampler */
