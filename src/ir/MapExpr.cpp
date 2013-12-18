#include "MapExpr.h"

namespace swift { namespace ir {

MapExpr::MapExpr() {
}

MapExpr::~MapExpr() {
}

size_t MapExpr::mapSize() {
  return argSize() / 2;
}

void MapExpr::addMap(std::shared_ptr<Expr> a, std::shared_ptr<Expr> b) {
  addArg(a);
  addArg(b);
}

std::shared_ptr<Expr> MapExpr::getFrom(int k) {
  return get(2 * k);
}

std::shared_ptr<Expr> MapExpr::getTo(int k) {
  return get(2 * k + 1);
}

const Ty* MapExpr::getFromTyp() {
  return fromTyp;
}

const Ty* MapExpr::getToTyp() {
  return toTyp;
}

void MapExpr::setFromTyp(const Ty * t) {
  fromTyp = t;
}

void MapExpr::setToTyp(const Ty * t) {
  toTyp = t;
}

}
}