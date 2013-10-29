/*
 * Absyn.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#ifndef ABSYN_H_
#define ABSYN_H_

namespace swift {

enum AbsynConstant {
  ADD, MINUS
} ABSYN_CONSTANT;

class Absyn {
public:
  Absyn(int l, int c) : line(l), col(c) {}
  virtual ~Absyn();
  int line; // line number in original file
  int col; // column number in original file
};

} /* namespace swift */

#endif /* ABSYN_H_ */
