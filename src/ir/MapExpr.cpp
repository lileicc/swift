#include "MapExpr.h"

namespace swift { namespace ir {

MapExpr::MapExpr() {
}

MapExpr::~MapExpr() {
}

size_t MapExpr::mapSize() {
  return argSize() / 2;
}

void MapExpr::addMap(Expr* a, Expr* b) {
  addArg(a);
  addArg(b);
}

Expr* MapExpr::getFrom(int k) {
  return get(2 * k);
}

Expr* MapExpr::getTo(int k) {
  return get(2 * k + 1);
}

Ty* MapExpr::getFromTyp() {
  return fromTyp;
}

Ty* MapExpr::getToTyp() {
  return toTyp;
}

void MapExpr::setFromTyp(Ty * t) {
  fromTyp = t;
}

void MapExpr::setToTyp(Ty * t) {
  toTyp = t;
}

}
}