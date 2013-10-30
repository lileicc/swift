/*
* MapExpr.cpp
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#include "MapExpr.h"

namespace swift {

MapExpr::MapExpr(int l, int c) :Expr(l, c) {
}

MapExpr::~MapExpr() {
}

int MapExpr::mapSize() {
	return args.size() / 2;
}

Expr* MapExpr::getFrom(int k) {
	return args[k << 1];
}

Expr* MapExpr::getTo(int k) {
	return args[(k << 1) | 1];
}

void MapExpr::addMap(Expr* from, Expr* to) {
	args.push_back(from);
	args.push_back(to);
}

}