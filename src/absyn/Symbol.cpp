/*
* Symbol.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "Symbol.h"

namespace swift{

Symbol::Symbol(string v) :value(v) {
}

Symbol::~Symbol() {
}

const string& Symbol::getValue() {
	return value;
}

}