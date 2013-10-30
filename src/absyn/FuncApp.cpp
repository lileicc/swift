/*
* FuncApp.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "FuncApp.h"

namespace swift{

FuncApp::FuncApp(int l, int c, Symbol func)
	:Expr(l,c), func(func) {
}

FuncApp::~FuncApp() {
}

const Symbol& FuncApp::getFunc() {
	return func;
}

}