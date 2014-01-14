/*
 * TimeStamp.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#include "TimeStampLiteral.h"

namespace swift {
namespace absyn {

TimeStampLiteral::TimeStampLiteral(int l, int c, int value) :
    Literal(l, c), value(value) {
}

TimeStampLiteral::~TimeStampLiteral() {
}

int TimeStampLiteral::getValue() {
  return value;
}

// For Debugging Use
void TimeStampLiteral::print(FILE* file, int indent) {
  fprintf(file, "%*s(TimeStampLiteral: @%d )\n", indent, "", value);
}

}
}
